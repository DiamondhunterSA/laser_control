import time
import cv2
from duijiao import calculate_sharpness

from devices_camera import (
    frame2mat,
    open_camera,
    close_camera,
    save_frame_with_timestamp,
    put_chinese_text,
)
from devices_stage import move_stage_zabsolute, wait_z_idle


class AutoFocusWithDisplay:
    def __init__(self, camera_index=0):
        self.camera_index = camera_index
        self.camera = None
        self.window_name = "自动对焦 - 实时显示"
        self.display_enabled = True
        self.save_images = False

    def open_camera(self):
        self.camera = open_camera(self.camera_index)
        return self.camera is not None

    def capture_with_display(self, z_position, sharpness=None, delay_ms=1000):
        if self.camera is None:
            return None, 0

        try:
            frame = self.camera.GetFrame(4000)
            mat = frame2mat(frame)

            if mat is None:
                return None, 0

            sharpness_val = calculate_sharpness(mat) if sharpness is None else sharpness

            if self.display_enabled:
                display_img = mat.copy()
                display_img = put_chinese_text(display_img, f"Z位置: {z_position}", (10, 10), text_size=24)
                display_img = put_chinese_text(display_img, f"清晰度: {sharpness_val:.2f}", (10, 40), text_size=24)
                cv2.imshow(self.window_name, display_img)

                key = cv2.waitKey(delay_ms) & 0xFF
                if key == 27:
                    print("用户中断自动对焦")
                    return None, sharpness_val
                if key == ord("s") or key == ord("S"):
                    save_frame_with_timestamp(mat, f"focus_z{z_position}")
                if key == ord(" "):
                    cv2.waitKey(0)

            if self.save_images:
                save_frame_with_timestamp(mat, f"auto_z{z_position}")

            return mat, sharpness_val
        except Exception as e:
            print(f"捕获/显示图像失败: {e}")
            return None, 0

    def close(self):
        if self.camera is not None:
            close_camera(self.camera)
            self.camera = None
        cv2.destroyAllWindows()


def auto_focus_with_display(start_z, search_range=200, step=10, camera_index=0, display_enabled=True, save_images=True):
    print("开始自动对焦搜索（带实时显示）...")
    af = AutoFocusWithDisplay(camera_index)
    af.display_enabled = display_enabled
    af.save_images = save_images

    if not af.open_camera():
        return start_z, 0, []

    try:
        min_z = start_z - search_range
        max_z = start_z + search_range
        best_z = start_z
        best_sharpness = -1
        sharpness_data = []

        move_stage_zabsolute(start_z)
        if not wait_z_idle():
            return start_z, 0, []

        time.sleep(0.5)
        start_mat, initial_sharpness = af.capture_with_display(start_z, delay_ms=3000)
        if start_mat is None:
            return start_z, 0, []

        sharpness_data.append((start_z, initial_sharpness))
        best_sharpness = initial_sharpness

        current_z = start_z
        while current_z >= min_z:
            test_z = current_z - step
            if test_z < min_z:
                break
            move_stage_zabsolute(test_z)
            if not wait_z_idle():
                break
            time.sleep(0.3)
            mat, sharpness = af.capture_with_display(test_z, delay_ms=1000)
            if mat is None:
                break
            sharpness_data.append((test_z, sharpness))
            if sharpness > best_sharpness:
                best_sharpness = sharpness
                best_z = test_z
            current_z = test_z

        current_z = start_z
        while current_z <= max_z:
            test_z = current_z + step
            if test_z > max_z:
                break
            move_stage_zabsolute(test_z)
            if not wait_z_idle():
                break
            time.sleep(0.3)
            mat, sharpness = af.capture_with_display(test_z, delay_ms=1000)
            if mat is None:
                break
            sharpness_data.append((test_z, sharpness))
            if sharpness > best_sharpness:
                best_sharpness = sharpness
                best_z = test_z
            current_z = test_z

        move_stage_zabsolute(best_z)
        wait_z_idle()
        time.sleep(0.5)

        best_mat, _ = af.capture_with_display(best_z, best_sharpness, delay_ms=5000)
        if best_mat is not None:
            save_frame_with_timestamp(best_mat, f"best_focus_z{best_z}")

        return best_z, best_sharpness, sharpness_data
    except Exception as e:
        print(f"自动对焦过程中出错: {e}")
        return start_z, 0, []
    finally:
        af.close()


def auto_focus_refine_with_display(best_z, refine_range=50, fine_step=2, camera_index=0):
    af = AutoFocusWithDisplay(camera_index)
    af.display_enabled = True

    if not af.open_camera():
        return best_z, 0

    try:
        refined_z = best_z
        refined_sharpness = -1
        min_z = best_z - refine_range
        max_z = best_z + refine_range

        for direction in [-1, 1]:
            current_z = best_z
            while True:
                test_z = current_z + direction * fine_step
                if test_z < min_z or test_z > max_z:
                    break

                move_stage_zabsolute(test_z)
                if not wait_z_idle():
                    break
                time.sleep(0.2)

                mat, sharpness = af.capture_with_display(test_z, delay_ms=1500)
                if mat is None:
                    break

                if sharpness > refined_sharpness:
                    refined_sharpness = sharpness
                    refined_z = test_z
                current_z = test_z

        move_stage_zabsolute(refined_z)
        wait_z_idle()
        time.sleep(0.5)

        final_mat, _ = af.capture_with_display(refined_z, refined_sharpness, delay_ms=5000)
        if final_mat is not None:
            save_frame_with_timestamp(final_mat, f"final_focus_z{refined_z}")

        return refined_z, refined_sharpness
    except Exception as e:
        print(f"精细对焦过程中出错: {e}")
        return best_z, 0
    finally:
        af.close()


def quick_auto_focus(start_z, camera_index=0, num_positions=5):
    af = AutoFocusWithDisplay(camera_index)
    af.display_enabled = True

    if not af.open_camera():
        return start_z, 0

    try:
        best_z = start_z
        best_sharpness = -1
        test_positions = [start_z + (i - num_positions // 2) * 50 for i in range(num_positions)]

        for test_z in test_positions:
            move_stage_zabsolute(test_z)
            if not wait_z_idle():
                continue
            time.sleep(0.3)
            mat, sharpness = af.capture_with_display(test_z, delay_ms=2000)
            if mat is None:
                break
            if sharpness > best_sharpness:
                best_sharpness = sharpness
                best_z = test_z

        move_stage_zabsolute(best_z)
        wait_z_idle()
        time.sleep(0.5)

        final_mat, _ = af.capture_with_display(best_z, best_sharpness, delay_ms=5000)
        if final_mat is not None:
            save_frame_with_timestamp(final_mat, f"quick_focus_z{best_z}")

        return best_z, best_sharpness
    except Exception as e:
        print(f"快速对焦过程中出错: {e}")
        return start_z, 0
    finally:
        af.close()
