## Clock Signal (100MHz Oscillator)
set_property -dict {PACKAGE_PIN W5 IOSTANDARD LVCMOS33} [get_ports clk_in1_0]
create_clock -period 10.000 -name sys_clk_pin -waveform {0.000 5.000} -add [get_ports clk_in1_0]

## System Reset (Center Button)
set_property -dict {PACKAGE_PIN U18 IOSTANDARD LVCMOS33} [get_ports reset]

## USB-UART Bridge (Mapped to axi_uartlite_0 for Laptop "Hello World")
## This allows you to see output over the existing USB cable
set_property -dict {PACKAGE_PIN B18 IOSTANDARD LVCMOS33} [get_ports tx_0]
set_property -dict {PACKAGE_PIN A18 IOSTANDARD LVCMOS33} [get_ports rx_0]

## PMOD JA (Upper Row) - Mapped to axi_uartlite_1 (Arduino Ready)
set_property -dict {PACKAGE_PIN J1 IOSTANDARD LVCMOS33} [get_ports tx_1]
set_property -dict {PACKAGE_PIN L2 IOSTANDARD LVCMOS33} [get_ports rx_1]

## PMOD JA (Lower Row) - Mapped to axi_uartlite_2 (Arduino Ready)
set_property -dict {PACKAGE_PIN H1 IOSTANDARD LVCMOS33} [get_ports tx_2]
set_property -dict {PACKAGE_PIN K2 IOSTANDARD LVCMOS33} [get_ports rx_2]

## PMOD JB (Upper Row) - Mapped to axi_uartlite_3 (Arduino Ready)
set_property -dict {PACKAGE_PIN A14 IOSTANDARD LVCMOS33} [get_ports tx_3]
set_property -dict {PACKAGE_PIN A16 IOSTANDARD LVCMOS33} [get_ports rx_3]

## PMOD JB (Lower Row) - Mapped to axi_uartlite_4 (Arduino Ready)
set_property -dict {PACKAGE_PIN A15 IOSTANDARD LVCMOS33} [get_ports tx_4]
set_property -dict {PACKAGE_PIN A17 IOSTANDARD LVCMOS33} [get_ports rx_4]

## Configuration Constraints
set_property CONFIG_VOLTAGE 3.3 [current_design]
set_property CFGBVS VCCO [current_design]
set_property CONFIG_MODE SPIx4 [current_design]