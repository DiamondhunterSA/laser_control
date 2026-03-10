import subprocess
import sys
import time

exe_path = r"E:\ccd\例程2-回零运动\test_faction2\test_faction2\bin\Debug\test_faction2.exe"

try:
    # 使用Popen非阻塞启动进程
    process = subprocess.Popen(
        [exe_path],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        universal_newlines=True,
        encoding='utf-8',
        bufsize=1  # 行缓冲，便于实时读取
    )

    print(f"已启动进程，PID: {process.pid}")
    print("正在等待程序输出（最长等待30秒）...")

    # 等待一段时间，并尝试读取输出
    timeout = 30
    start_time = time.time()

    while True:
        # 检查是否有输出可读
        output_line = process.stdout.readline()
        if output_line:
            print(f"[程序输出] {output_line.rstrip()}")

        # 检查是否超时
        if time.time() - start_time > timeout:
            print(f"\n警告：等待超过 {timeout} 秒，即将终止程序。")
            process.terminate()  # 先尝试温和终止
            time.sleep(2)
            if process.poll() is None:  # 如果还在运行
                process.kill()  # 强制终止
            print("程序已被终止。")
            break

        # 检查进程是否已结束
        return_code = process.poll()
        if return_code is not None:
            print(f"\n程序已执行完毕，返回码: {return_code}")
            # 读取剩余的所有输出
            remaining_output, errors = process.communicate()
            if remaining_output:
                print(f"[最后输出] {remaining_output}")
            if errors:
                print(f"[错误信息] {errors}")
            break

        # 避免CPU占用过高
        time.sleep(0.1)

except FileNotFoundError:
    print(f"错误：找不到可执行文件 '{exe_path}'")
except Exception as e:
    print(f"执行过程中发生错误：{e}")