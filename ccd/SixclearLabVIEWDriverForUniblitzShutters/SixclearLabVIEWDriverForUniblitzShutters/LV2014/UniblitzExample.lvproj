<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="14008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="driver" Type="Folder">
			<Property Name="NI.SortType" Type="Int">3</Property>
			<Item Name="support" Type="Folder">
				<Item Name="UNBILITZ-SimulationFunctionalGlobal.vi" Type="VI" URL="../driver/UNBILITZ-SimulationFunctionalGlobal.vi"/>
				<Item Name="UNIBLITZ-Address.ctl" Type="VI" URL="../driver/UNIBLITZ-Address.ctl"/>
				<Item Name="UNIBLITZ-Operation.ctl" Type="VI" URL="../driver/UNIBLITZ-Operation.ctl"/>
				<Item Name="UNIBLITZ-SimulationModeOperation.ctl" Type="VI" URL="../driver/UNIBLITZ-SimulationModeOperation.ctl"/>
				<Item Name="UNIBLITZ-SteadyState.ctl" Type="VI" URL="../driver/UNIBLITZ-SteadyState.ctl"/>
			</Item>
			<Item Name="UNBILITZ-ShutterDriver-Open.vi" Type="VI" URL="../driver/UNBILITZ-ShutterDriver-Open.vi"/>
			<Item Name="UNBILITZ-ShutterDriver-Control.vi" Type="VI" URL="../driver/UNBILITZ-ShutterDriver-Control.vi"/>
			<Item Name="UNBILITZ-ShutterDriver-Close.vi" Type="VI" URL="../driver/UNBILITZ-ShutterDriver-Close.vi"/>
		</Item>
		<Item Name="Example.vi" Type="VI" URL="../Example.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="vi.lib" Type="Folder">
				<Item Name="VISA Configure Serial Port" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port"/>
				<Item Name="VISA Configure Serial Port (Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Instr).vi"/>
				<Item Name="VISA Configure Serial Port (Serial Instr).vi" Type="VI" URL="/&lt;vilib&gt;/Instr/_visa.llb/VISA Configure Serial Port (Serial Instr).vi"/>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
