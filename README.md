# Picomini
Open-source CNC controller hardware.

Picomini 开源运动控制板（固件仓库）<br>
本仓库包含 Picomini 开源运动控制板的固件。控制板主要面向 grblHAL
运动控制固件设计，也可用于 CNC、雕刻、激光及自动化设备。

项目概述<br>
Picomini 是一款基于 RP2040 的多轴运动控制板，提供完整的步进电机脉冲输出、主轴控制、输入输
出隔离以及扩展接口。本仓库仅包含硬件相关内容，不包含固件或上位机软件。

主要特性<br>
◆ 兼容 Ultimate Pico（RP2040）<br>
◆ 4 轴最高 200 kHz 脉冲输出<br>
◆ 主轴 0–10V 模拟量速度控制（PWM 放大）<br>
◆ 主轴 PWM / EN / DIR 同时支持继电器输出<br>
◆ 8 路光耦隔离输入，支持 5V / 12V / 24V<br>
◆ 6 路继电器输出，支持冷却、喷雾、照明等<br>
◆ USB 或以太网通信（W5100S / W5500）<br>
◆ 1 路 UART / I2C 扩展接口<br>
