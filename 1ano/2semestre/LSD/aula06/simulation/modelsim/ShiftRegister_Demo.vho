-- Copyright (C) 2020  Intel Corporation. All rights reserved.
-- Your use of Intel Corporation's design tools, logic functions 
-- and other software and tools, and any partner logic 
-- functions, and any output files from any of the foregoing 
-- (including device programming or simulation files), and any 
-- associated documentation or information are expressly subject 
-- to the terms and conditions of the Intel Program License 
-- Subscription Agreement, the Intel Quartus Prime License Agreement,
-- the Intel FPGA IP License Agreement, or other applicable license
-- agreement, including, without limitation, that your use is for
-- the sole purpose of programming logic devices manufactured by
-- Intel and sold by Intel or its authorized distributors.  Please
-- refer to the applicable agreement for further details, at
-- https://fpgasoftware.intel.com/eula.

-- VENDOR "Altera"
-- PROGRAM "Quartus Prime"
-- VERSION "Version 20.1.1 Build 720 11/11/2020 SJ Lite Edition"

-- DATE "04/04/2024 14:42:51"

-- 
-- Device: Altera EP4CE115F29C7 Package FBGA780
-- 

-- 
-- This VHDL file should be used for ModelSim-Altera (VHDL) only
-- 

LIBRARY CYCLONEIVE;
LIBRARY IEEE;
USE CYCLONEIVE.CYCLONEIVE_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	hard_block IS
    PORT (
	devoe : IN std_logic;
	devclrn : IN std_logic;
	devpor : IN std_logic
	);
END hard_block;

-- Design Ports Information
-- ~ALTERA_ASDO_DATA1~	=>  Location: PIN_F4,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- ~ALTERA_FLASH_nCE_nCSO~	=>  Location: PIN_E2,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- ~ALTERA_DCLK~	=>  Location: PIN_P3,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- ~ALTERA_DATA0~	=>  Location: PIN_N7,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- ~ALTERA_nCEO~	=>  Location: PIN_P28,	 I/O Standard: 2.5 V,	 Current Strength: 8mA


ARCHITECTURE structure OF hard_block IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL \~ALTERA_ASDO_DATA1~~padout\ : std_logic;
SIGNAL \~ALTERA_FLASH_nCE_nCSO~~padout\ : std_logic;
SIGNAL \~ALTERA_DATA0~~padout\ : std_logic;
SIGNAL \~ALTERA_ASDO_DATA1~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_FLASH_nCE_nCSO~~ibuf_o\ : std_logic;
SIGNAL \~ALTERA_DATA0~~ibuf_o\ : std_logic;

BEGIN

ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;
END structure;


LIBRARY ALTERA;
LIBRARY CYCLONEIVE;
LIBRARY IEEE;
USE ALTERA.ALTERA_PRIMITIVES_COMPONENTS.ALL;
USE CYCLONEIVE.CYCLONEIVE_COMPONENTS.ALL;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY 	ShiftRegister_Demo IS
    PORT (
	SW : IN std_logic_vector(2 DOWNTO 0);
	CLOCK_50 : IN std_logic;
	LEDR : BUFFER std_logic_vector(7 DOWNTO 0)
	);
END ShiftRegister_Demo;

-- Design Ports Information
-- LEDR[0]	=>  Location: PIN_G19,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- LEDR[1]	=>  Location: PIN_F19,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- LEDR[2]	=>  Location: PIN_E19,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- LEDR[3]	=>  Location: PIN_F21,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- LEDR[4]	=>  Location: PIN_F18,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- LEDR[5]	=>  Location: PIN_E18,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- LEDR[6]	=>  Location: PIN_J19,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- LEDR[7]	=>  Location: PIN_H19,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SW[0]	=>  Location: PIN_AB28,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SW[1]	=>  Location: PIN_AC28,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- SW[2]	=>  Location: PIN_AC27,	 I/O Standard: 2.5 V,	 Current Strength: Default
-- CLOCK_50	=>  Location: PIN_Y2,	 I/O Standard: 2.5 V,	 Current Strength: Default


ARCHITECTURE structure OF ShiftRegister_Demo IS
SIGNAL gnd : std_logic := '0';
SIGNAL vcc : std_logic := '1';
SIGNAL unknown : std_logic := 'X';
SIGNAL devoe : std_logic := '1';
SIGNAL devclrn : std_logic := '1';
SIGNAL devpor : std_logic := '1';
SIGNAL ww_devoe : std_logic;
SIGNAL ww_devclrn : std_logic;
SIGNAL ww_devpor : std_logic;
SIGNAL ww_SW : std_logic_vector(2 DOWNTO 0);
SIGNAL ww_CLOCK_50 : std_logic;
SIGNAL ww_LEDR : std_logic_vector(7 DOWNTO 0);
SIGNAL \CLOCK_50~inputclkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \ClkDividerN|clkOut~clkctrl_INCLK_bus\ : std_logic_vector(3 DOWNTO 0);
SIGNAL \LEDR[0]~output_o\ : std_logic;
SIGNAL \LEDR[1]~output_o\ : std_logic;
SIGNAL \LEDR[2]~output_o\ : std_logic;
SIGNAL \LEDR[3]~output_o\ : std_logic;
SIGNAL \LEDR[4]~output_o\ : std_logic;
SIGNAL \LEDR[5]~output_o\ : std_logic;
SIGNAL \LEDR[6]~output_o\ : std_logic;
SIGNAL \LEDR[7]~output_o\ : std_logic;
SIGNAL \CLOCK_50~input_o\ : std_logic;
SIGNAL \CLOCK_50~inputclkctrl_outclk\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[0]~26_combout\ : std_logic;
SIGNAL \ClkDividerN|LessThan0~2_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[19]~65\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[20]~66_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[20]~67\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[21]~68_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[21]~69\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[22]~70_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[22]~71\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[23]~72_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[23]~73\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[24]~74_combout\ : std_logic;
SIGNAL \ClkDividerN|LessThan0~3_combout\ : std_logic;
SIGNAL \ClkDividerN|LessThan0~0_combout\ : std_logic;
SIGNAL \ClkDividerN|clkOut~3_combout\ : std_logic;
SIGNAL \ClkDividerN|clkOut~0_combout\ : std_logic;
SIGNAL \ClkDividerN|clkOut~1_combout\ : std_logic;
SIGNAL \ClkDividerN|LessThan0~1_combout\ : std_logic;
SIGNAL \ClkDividerN|LessThan0~6_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[0]~27\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[1]~28_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[1]~29\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[2]~30_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[2]~31\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[3]~32_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[3]~33\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[4]~34_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[4]~35\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[5]~36_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[5]~37\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[6]~38_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[6]~39\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[7]~40_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[7]~41\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[8]~42_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[8]~43\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[9]~44_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[9]~45\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[10]~46_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[10]~47\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[11]~48_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[11]~49\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[12]~50_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[12]~51\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[13]~52_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[13]~53\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[14]~54_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[14]~55\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[15]~56_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[15]~57\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[16]~58_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[16]~59\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[17]~60_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[17]~61\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[18]~62_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[18]~63\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[19]~64_combout\ : std_logic;
SIGNAL \ClkDividerN|clkOut~4_combout\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[24]~75\ : std_logic;
SIGNAL \ClkDividerN|s_divCounter[25]~76_combout\ : std_logic;
SIGNAL \ClkDividerN|LessThan0~4_combout\ : std_logic;
SIGNAL \ClkDividerN|LessThan0~5_combout\ : std_logic;
SIGNAL \ClkDividerN|clkOut~2_combout\ : std_logic;
SIGNAL \ClkDividerN|clkOut~5_combout\ : std_logic;
SIGNAL \ClkDividerN|clkOut~6_combout\ : std_logic;
SIGNAL \ClkDividerN|clkOut~7_combout\ : std_logic;
SIGNAL \ClkDividerN|clkOut~8_combout\ : std_logic;
SIGNAL \ClkDividerN|clkOut~9_combout\ : std_logic;
SIGNAL \ClkDividerN|clkOut~q\ : std_logic;
SIGNAL \ClkDividerN|clkOut~clkctrl_outclk\ : std_logic;
SIGNAL \SW[0]~input_o\ : std_logic;
SIGNAL \SW[1]~input_o\ : std_logic;
SIGNAL \system|aux~7_combout\ : std_logic;
SIGNAL \SW[2]~input_o\ : std_logic;
SIGNAL \system|aux~6_combout\ : std_logic;
SIGNAL \system|aux~5_combout\ : std_logic;
SIGNAL \system|aux~4_combout\ : std_logic;
SIGNAL \system|aux~3_combout\ : std_logic;
SIGNAL \system|aux~2_combout\ : std_logic;
SIGNAL \system|aux~1_combout\ : std_logic;
SIGNAL \system|aux~0_combout\ : std_logic;
SIGNAL \system|aux\ : std_logic_vector(7 DOWNTO 0);
SIGNAL \ClkDividerN|s_divCounter\ : std_logic_vector(25 DOWNTO 0);

COMPONENT hard_block
    PORT (
	devoe : IN std_logic;
	devclrn : IN std_logic;
	devpor : IN std_logic);
END COMPONENT;

BEGIN

ww_SW <= SW;
ww_CLOCK_50 <= CLOCK_50;
LEDR <= ww_LEDR;
ww_devoe <= devoe;
ww_devclrn <= devclrn;
ww_devpor <= devpor;

\CLOCK_50~inputclkctrl_INCLK_bus\ <= (vcc & vcc & vcc & \CLOCK_50~input_o\);

\ClkDividerN|clkOut~clkctrl_INCLK_bus\ <= (vcc & vcc & vcc & \ClkDividerN|clkOut~q\);
auto_generated_inst : hard_block
PORT MAP (
	devoe => ww_devoe,
	devclrn => ww_devclrn,
	devpor => ww_devpor);

-- Location: IOOBUF_X69_Y73_N16
\LEDR[0]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \system|aux\(0),
	devoe => ww_devoe,
	o => \LEDR[0]~output_o\);

-- Location: IOOBUF_X94_Y73_N2
\LEDR[1]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \system|aux\(1),
	devoe => ww_devoe,
	o => \LEDR[1]~output_o\);

-- Location: IOOBUF_X94_Y73_N9
\LEDR[2]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \system|aux\(2),
	devoe => ww_devoe,
	o => \LEDR[2]~output_o\);

-- Location: IOOBUF_X107_Y73_N16
\LEDR[3]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \system|aux\(3),
	devoe => ww_devoe,
	o => \LEDR[3]~output_o\);

-- Location: IOOBUF_X87_Y73_N16
\LEDR[4]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \system|aux\(4),
	devoe => ww_devoe,
	o => \LEDR[4]~output_o\);

-- Location: IOOBUF_X87_Y73_N9
\LEDR[5]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \system|aux\(5),
	devoe => ww_devoe,
	o => \LEDR[5]~output_o\);

-- Location: IOOBUF_X72_Y73_N9
\LEDR[6]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \system|aux\(6),
	devoe => ww_devoe,
	o => \LEDR[6]~output_o\);

-- Location: IOOBUF_X72_Y73_N2
\LEDR[7]~output\ : cycloneive_io_obuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	open_drain_output => "false")
-- pragma translate_on
PORT MAP (
	i => \system|aux\(7),
	devoe => ww_devoe,
	o => \LEDR[7]~output_o\);

-- Location: IOIBUF_X0_Y36_N15
\CLOCK_50~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_CLOCK_50,
	o => \CLOCK_50~input_o\);

-- Location: CLKCTRL_G4
\CLOCK_50~inputclkctrl\ : cycloneive_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \CLOCK_50~inputclkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \CLOCK_50~inputclkctrl_outclk\);

-- Location: LCCOMB_X55_Y71_N6
\ClkDividerN|s_divCounter[0]~26\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[0]~26_combout\ = \ClkDividerN|s_divCounter\(0) $ (VCC)
-- \ClkDividerN|s_divCounter[0]~27\ = CARRY(\ClkDividerN|s_divCounter\(0))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101010110101010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(0),
	datad => VCC,
	combout => \ClkDividerN|s_divCounter[0]~26_combout\,
	cout => \ClkDividerN|s_divCounter[0]~27\);

-- Location: LCCOMB_X56_Y71_N6
\ClkDividerN|LessThan0~2\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|LessThan0~2_combout\ = (((!\ClkDividerN|s_divCounter\(12)) # (!\ClkDividerN|s_divCounter\(13))) # (!\ClkDividerN|s_divCounter\(15))) # (!\ClkDividerN|s_divCounter\(14))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0111111111111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(14),
	datab => \ClkDividerN|s_divCounter\(15),
	datac => \ClkDividerN|s_divCounter\(13),
	datad => \ClkDividerN|s_divCounter\(12),
	combout => \ClkDividerN|LessThan0~2_combout\);

-- Location: LCCOMB_X55_Y70_N12
\ClkDividerN|s_divCounter[19]~64\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[19]~64_combout\ = (\ClkDividerN|s_divCounter\(19) & (!\ClkDividerN|s_divCounter[18]~63\)) # (!\ClkDividerN|s_divCounter\(19) & ((\ClkDividerN|s_divCounter[18]~63\) # (GND)))
-- \ClkDividerN|s_divCounter[19]~65\ = CARRY((!\ClkDividerN|s_divCounter[18]~63\) # (!\ClkDividerN|s_divCounter\(19)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(19),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[18]~63\,
	combout => \ClkDividerN|s_divCounter[19]~64_combout\,
	cout => \ClkDividerN|s_divCounter[19]~65\);

-- Location: LCCOMB_X55_Y70_N14
\ClkDividerN|s_divCounter[20]~66\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[20]~66_combout\ = (\ClkDividerN|s_divCounter\(20) & (\ClkDividerN|s_divCounter[19]~65\ $ (GND))) # (!\ClkDividerN|s_divCounter\(20) & (!\ClkDividerN|s_divCounter[19]~65\ & VCC))
-- \ClkDividerN|s_divCounter[20]~67\ = CARRY((\ClkDividerN|s_divCounter\(20) & !\ClkDividerN|s_divCounter[19]~65\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \ClkDividerN|s_divCounter\(20),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[19]~65\,
	combout => \ClkDividerN|s_divCounter[20]~66_combout\,
	cout => \ClkDividerN|s_divCounter[20]~67\);

-- Location: FF_X55_Y70_N15
\ClkDividerN|s_divCounter[20]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[20]~66_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(20));

-- Location: LCCOMB_X55_Y70_N16
\ClkDividerN|s_divCounter[21]~68\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[21]~68_combout\ = (\ClkDividerN|s_divCounter\(21) & (!\ClkDividerN|s_divCounter[20]~67\)) # (!\ClkDividerN|s_divCounter\(21) & ((\ClkDividerN|s_divCounter[20]~67\) # (GND)))
-- \ClkDividerN|s_divCounter[21]~69\ = CARRY((!\ClkDividerN|s_divCounter[20]~67\) # (!\ClkDividerN|s_divCounter\(21)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \ClkDividerN|s_divCounter\(21),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[20]~67\,
	combout => \ClkDividerN|s_divCounter[21]~68_combout\,
	cout => \ClkDividerN|s_divCounter[21]~69\);

-- Location: FF_X55_Y70_N17
\ClkDividerN|s_divCounter[21]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[21]~68_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(21));

-- Location: LCCOMB_X55_Y70_N18
\ClkDividerN|s_divCounter[22]~70\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[22]~70_combout\ = (\ClkDividerN|s_divCounter\(22) & (\ClkDividerN|s_divCounter[21]~69\ $ (GND))) # (!\ClkDividerN|s_divCounter\(22) & (!\ClkDividerN|s_divCounter[21]~69\ & VCC))
-- \ClkDividerN|s_divCounter[22]~71\ = CARRY((\ClkDividerN|s_divCounter\(22) & !\ClkDividerN|s_divCounter[21]~69\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \ClkDividerN|s_divCounter\(22),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[21]~69\,
	combout => \ClkDividerN|s_divCounter[22]~70_combout\,
	cout => \ClkDividerN|s_divCounter[22]~71\);

-- Location: FF_X55_Y70_N19
\ClkDividerN|s_divCounter[22]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[22]~70_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(22));

-- Location: LCCOMB_X55_Y70_N20
\ClkDividerN|s_divCounter[23]~72\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[23]~72_combout\ = (\ClkDividerN|s_divCounter\(23) & (!\ClkDividerN|s_divCounter[22]~71\)) # (!\ClkDividerN|s_divCounter\(23) & ((\ClkDividerN|s_divCounter[22]~71\) # (GND)))
-- \ClkDividerN|s_divCounter[23]~73\ = CARRY((!\ClkDividerN|s_divCounter[22]~71\) # (!\ClkDividerN|s_divCounter\(23)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \ClkDividerN|s_divCounter\(23),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[22]~71\,
	combout => \ClkDividerN|s_divCounter[23]~72_combout\,
	cout => \ClkDividerN|s_divCounter[23]~73\);

-- Location: FF_X55_Y70_N21
\ClkDividerN|s_divCounter[23]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[23]~72_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(23));

-- Location: LCCOMB_X55_Y70_N22
\ClkDividerN|s_divCounter[24]~74\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[24]~74_combout\ = (\ClkDividerN|s_divCounter\(24) & (\ClkDividerN|s_divCounter[23]~73\ $ (GND))) # (!\ClkDividerN|s_divCounter\(24) & (!\ClkDividerN|s_divCounter[23]~73\ & VCC))
-- \ClkDividerN|s_divCounter[24]~75\ = CARRY((\ClkDividerN|s_divCounter\(24) & !\ClkDividerN|s_divCounter[23]~73\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(24),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[23]~73\,
	combout => \ClkDividerN|s_divCounter[24]~74_combout\,
	cout => \ClkDividerN|s_divCounter[24]~75\);

-- Location: FF_X55_Y70_N23
\ClkDividerN|s_divCounter[24]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[24]~74_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(24));

-- Location: LCCOMB_X56_Y71_N16
\ClkDividerN|LessThan0~3\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|LessThan0~3_combout\ = (\ClkDividerN|LessThan0~2_combout\ & (!\ClkDividerN|s_divCounter\(24) & (!\ClkDividerN|s_divCounter\(18) & !\ClkDividerN|s_divCounter\(16))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|LessThan0~2_combout\,
	datab => \ClkDividerN|s_divCounter\(24),
	datac => \ClkDividerN|s_divCounter\(18),
	datad => \ClkDividerN|s_divCounter\(16),
	combout => \ClkDividerN|LessThan0~3_combout\);

-- Location: LCCOMB_X56_Y71_N10
\ClkDividerN|LessThan0~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|LessThan0~0_combout\ = (!\ClkDividerN|s_divCounter\(18) & (!\ClkDividerN|s_divCounter\(11) & (!\ClkDividerN|s_divCounter\(16) & !\ClkDividerN|s_divCounter\(24))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(18),
	datab => \ClkDividerN|s_divCounter\(11),
	datac => \ClkDividerN|s_divCounter\(16),
	datad => \ClkDividerN|s_divCounter\(24),
	combout => \ClkDividerN|LessThan0~0_combout\);

-- Location: LCCOMB_X55_Y71_N4
\ClkDividerN|clkOut~3\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|clkOut~3_combout\ = (!\ClkDividerN|s_divCounter\(8) & (!\ClkDividerN|s_divCounter\(7) & (!\ClkDividerN|s_divCounter\(10) & !\ClkDividerN|s_divCounter\(9))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000001",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(8),
	datab => \ClkDividerN|s_divCounter\(7),
	datac => \ClkDividerN|s_divCounter\(10),
	datad => \ClkDividerN|s_divCounter\(9),
	combout => \ClkDividerN|clkOut~3_combout\);

-- Location: LCCOMB_X55_Y71_N0
\ClkDividerN|clkOut~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|clkOut~0_combout\ = (\ClkDividerN|s_divCounter\(2) & (\ClkDividerN|s_divCounter\(1) & (\ClkDividerN|s_divCounter\(0) & \ClkDividerN|s_divCounter\(3))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(2),
	datab => \ClkDividerN|s_divCounter\(1),
	datac => \ClkDividerN|s_divCounter\(0),
	datad => \ClkDividerN|s_divCounter\(3),
	combout => \ClkDividerN|clkOut~0_combout\);

-- Location: LCCOMB_X55_Y71_N2
\ClkDividerN|clkOut~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|clkOut~1_combout\ = (\ClkDividerN|s_divCounter\(5) & (\ClkDividerN|s_divCounter\(4) & \ClkDividerN|clkOut~0_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \ClkDividerN|s_divCounter\(5),
	datac => \ClkDividerN|s_divCounter\(4),
	datad => \ClkDividerN|clkOut~0_combout\,
	combout => \ClkDividerN|clkOut~1_combout\);

-- Location: LCCOMB_X56_Y71_N18
\ClkDividerN|LessThan0~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|LessThan0~1_combout\ = (\ClkDividerN|LessThan0~0_combout\ & (\ClkDividerN|clkOut~3_combout\ & ((!\ClkDividerN|clkOut~1_combout\) # (!\ClkDividerN|s_divCounter\(6)))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010000010100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|LessThan0~0_combout\,
	datab => \ClkDividerN|s_divCounter\(6),
	datac => \ClkDividerN|clkOut~3_combout\,
	datad => \ClkDividerN|clkOut~1_combout\,
	combout => \ClkDividerN|LessThan0~1_combout\);

-- Location: LCCOMB_X56_Y71_N30
\ClkDividerN|LessThan0~6\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|LessThan0~6_combout\ = (!\ClkDividerN|LessThan0~3_combout\ & (!\ClkDividerN|LessThan0~5_combout\ & !\ClkDividerN|LessThan0~1_combout\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000000000011",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \ClkDividerN|LessThan0~3_combout\,
	datac => \ClkDividerN|LessThan0~5_combout\,
	datad => \ClkDividerN|LessThan0~1_combout\,
	combout => \ClkDividerN|LessThan0~6_combout\);

-- Location: FF_X55_Y71_N7
\ClkDividerN|s_divCounter[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[0]~26_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(0));

-- Location: LCCOMB_X55_Y71_N8
\ClkDividerN|s_divCounter[1]~28\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[1]~28_combout\ = (\ClkDividerN|s_divCounter\(1) & (!\ClkDividerN|s_divCounter[0]~27\)) # (!\ClkDividerN|s_divCounter\(1) & ((\ClkDividerN|s_divCounter[0]~27\) # (GND)))
-- \ClkDividerN|s_divCounter[1]~29\ = CARRY((!\ClkDividerN|s_divCounter[0]~27\) # (!\ClkDividerN|s_divCounter\(1)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \ClkDividerN|s_divCounter\(1),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[0]~27\,
	combout => \ClkDividerN|s_divCounter[1]~28_combout\,
	cout => \ClkDividerN|s_divCounter[1]~29\);

-- Location: FF_X55_Y71_N9
\ClkDividerN|s_divCounter[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[1]~28_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(1));

-- Location: LCCOMB_X55_Y71_N10
\ClkDividerN|s_divCounter[2]~30\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[2]~30_combout\ = (\ClkDividerN|s_divCounter\(2) & (\ClkDividerN|s_divCounter[1]~29\ $ (GND))) # (!\ClkDividerN|s_divCounter\(2) & (!\ClkDividerN|s_divCounter[1]~29\ & VCC))
-- \ClkDividerN|s_divCounter[2]~31\ = CARRY((\ClkDividerN|s_divCounter\(2) & !\ClkDividerN|s_divCounter[1]~29\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(2),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[1]~29\,
	combout => \ClkDividerN|s_divCounter[2]~30_combout\,
	cout => \ClkDividerN|s_divCounter[2]~31\);

-- Location: FF_X55_Y71_N11
\ClkDividerN|s_divCounter[2]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[2]~30_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(2));

-- Location: LCCOMB_X55_Y71_N12
\ClkDividerN|s_divCounter[3]~32\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[3]~32_combout\ = (\ClkDividerN|s_divCounter\(3) & (!\ClkDividerN|s_divCounter[2]~31\)) # (!\ClkDividerN|s_divCounter\(3) & ((\ClkDividerN|s_divCounter[2]~31\) # (GND)))
-- \ClkDividerN|s_divCounter[3]~33\ = CARRY((!\ClkDividerN|s_divCounter[2]~31\) # (!\ClkDividerN|s_divCounter\(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(3),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[2]~31\,
	combout => \ClkDividerN|s_divCounter[3]~32_combout\,
	cout => \ClkDividerN|s_divCounter[3]~33\);

-- Location: FF_X55_Y71_N13
\ClkDividerN|s_divCounter[3]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[3]~32_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(3));

-- Location: LCCOMB_X55_Y71_N14
\ClkDividerN|s_divCounter[4]~34\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[4]~34_combout\ = (\ClkDividerN|s_divCounter\(4) & (\ClkDividerN|s_divCounter[3]~33\ $ (GND))) # (!\ClkDividerN|s_divCounter\(4) & (!\ClkDividerN|s_divCounter[3]~33\ & VCC))
-- \ClkDividerN|s_divCounter[4]~35\ = CARRY((\ClkDividerN|s_divCounter\(4) & !\ClkDividerN|s_divCounter[3]~33\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \ClkDividerN|s_divCounter\(4),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[3]~33\,
	combout => \ClkDividerN|s_divCounter[4]~34_combout\,
	cout => \ClkDividerN|s_divCounter[4]~35\);

-- Location: FF_X55_Y71_N15
\ClkDividerN|s_divCounter[4]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[4]~34_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(4));

-- Location: LCCOMB_X55_Y71_N16
\ClkDividerN|s_divCounter[5]~36\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[5]~36_combout\ = (\ClkDividerN|s_divCounter\(5) & (!\ClkDividerN|s_divCounter[4]~35\)) # (!\ClkDividerN|s_divCounter\(5) & ((\ClkDividerN|s_divCounter[4]~35\) # (GND)))
-- \ClkDividerN|s_divCounter[5]~37\ = CARRY((!\ClkDividerN|s_divCounter[4]~35\) # (!\ClkDividerN|s_divCounter\(5)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \ClkDividerN|s_divCounter\(5),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[4]~35\,
	combout => \ClkDividerN|s_divCounter[5]~36_combout\,
	cout => \ClkDividerN|s_divCounter[5]~37\);

-- Location: FF_X55_Y71_N17
\ClkDividerN|s_divCounter[5]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[5]~36_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(5));

-- Location: LCCOMB_X55_Y71_N18
\ClkDividerN|s_divCounter[6]~38\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[6]~38_combout\ = (\ClkDividerN|s_divCounter\(6) & (\ClkDividerN|s_divCounter[5]~37\ $ (GND))) # (!\ClkDividerN|s_divCounter\(6) & (!\ClkDividerN|s_divCounter[5]~37\ & VCC))
-- \ClkDividerN|s_divCounter[6]~39\ = CARRY((\ClkDividerN|s_divCounter\(6) & !\ClkDividerN|s_divCounter[5]~37\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \ClkDividerN|s_divCounter\(6),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[5]~37\,
	combout => \ClkDividerN|s_divCounter[6]~38_combout\,
	cout => \ClkDividerN|s_divCounter[6]~39\);

-- Location: FF_X55_Y71_N19
\ClkDividerN|s_divCounter[6]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[6]~38_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(6));

-- Location: LCCOMB_X55_Y71_N20
\ClkDividerN|s_divCounter[7]~40\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[7]~40_combout\ = (\ClkDividerN|s_divCounter\(7) & (!\ClkDividerN|s_divCounter[6]~39\)) # (!\ClkDividerN|s_divCounter\(7) & ((\ClkDividerN|s_divCounter[6]~39\) # (GND)))
-- \ClkDividerN|s_divCounter[7]~41\ = CARRY((!\ClkDividerN|s_divCounter[6]~39\) # (!\ClkDividerN|s_divCounter\(7)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \ClkDividerN|s_divCounter\(7),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[6]~39\,
	combout => \ClkDividerN|s_divCounter[7]~40_combout\,
	cout => \ClkDividerN|s_divCounter[7]~41\);

-- Location: FF_X55_Y71_N21
\ClkDividerN|s_divCounter[7]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[7]~40_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(7));

-- Location: LCCOMB_X55_Y71_N22
\ClkDividerN|s_divCounter[8]~42\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[8]~42_combout\ = (\ClkDividerN|s_divCounter\(8) & (\ClkDividerN|s_divCounter[7]~41\ $ (GND))) # (!\ClkDividerN|s_divCounter\(8) & (!\ClkDividerN|s_divCounter[7]~41\ & VCC))
-- \ClkDividerN|s_divCounter[8]~43\ = CARRY((\ClkDividerN|s_divCounter\(8) & !\ClkDividerN|s_divCounter[7]~41\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(8),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[7]~41\,
	combout => \ClkDividerN|s_divCounter[8]~42_combout\,
	cout => \ClkDividerN|s_divCounter[8]~43\);

-- Location: FF_X55_Y71_N23
\ClkDividerN|s_divCounter[8]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[8]~42_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(8));

-- Location: LCCOMB_X55_Y71_N24
\ClkDividerN|s_divCounter[9]~44\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[9]~44_combout\ = (\ClkDividerN|s_divCounter\(9) & (!\ClkDividerN|s_divCounter[8]~43\)) # (!\ClkDividerN|s_divCounter\(9) & ((\ClkDividerN|s_divCounter[8]~43\) # (GND)))
-- \ClkDividerN|s_divCounter[9]~45\ = CARRY((!\ClkDividerN|s_divCounter[8]~43\) # (!\ClkDividerN|s_divCounter\(9)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \ClkDividerN|s_divCounter\(9),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[8]~43\,
	combout => \ClkDividerN|s_divCounter[9]~44_combout\,
	cout => \ClkDividerN|s_divCounter[9]~45\);

-- Location: FF_X55_Y71_N25
\ClkDividerN|s_divCounter[9]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[9]~44_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(9));

-- Location: LCCOMB_X55_Y71_N26
\ClkDividerN|s_divCounter[10]~46\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[10]~46_combout\ = (\ClkDividerN|s_divCounter\(10) & (\ClkDividerN|s_divCounter[9]~45\ $ (GND))) # (!\ClkDividerN|s_divCounter\(10) & (!\ClkDividerN|s_divCounter[9]~45\ & VCC))
-- \ClkDividerN|s_divCounter[10]~47\ = CARRY((\ClkDividerN|s_divCounter\(10) & !\ClkDividerN|s_divCounter[9]~45\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(10),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[9]~45\,
	combout => \ClkDividerN|s_divCounter[10]~46_combout\,
	cout => \ClkDividerN|s_divCounter[10]~47\);

-- Location: FF_X55_Y71_N27
\ClkDividerN|s_divCounter[10]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[10]~46_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(10));

-- Location: LCCOMB_X55_Y71_N28
\ClkDividerN|s_divCounter[11]~48\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[11]~48_combout\ = (\ClkDividerN|s_divCounter\(11) & (!\ClkDividerN|s_divCounter[10]~47\)) # (!\ClkDividerN|s_divCounter\(11) & ((\ClkDividerN|s_divCounter[10]~47\) # (GND)))
-- \ClkDividerN|s_divCounter[11]~49\ = CARRY((!\ClkDividerN|s_divCounter[10]~47\) # (!\ClkDividerN|s_divCounter\(11)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \ClkDividerN|s_divCounter\(11),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[10]~47\,
	combout => \ClkDividerN|s_divCounter[11]~48_combout\,
	cout => \ClkDividerN|s_divCounter[11]~49\);

-- Location: FF_X55_Y71_N29
\ClkDividerN|s_divCounter[11]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[11]~48_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(11));

-- Location: LCCOMB_X55_Y71_N30
\ClkDividerN|s_divCounter[12]~50\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[12]~50_combout\ = (\ClkDividerN|s_divCounter\(12) & (\ClkDividerN|s_divCounter[11]~49\ $ (GND))) # (!\ClkDividerN|s_divCounter\(12) & (!\ClkDividerN|s_divCounter[11]~49\ & VCC))
-- \ClkDividerN|s_divCounter[12]~51\ = CARRY((\ClkDividerN|s_divCounter\(12) & !\ClkDividerN|s_divCounter[11]~49\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(12),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[11]~49\,
	combout => \ClkDividerN|s_divCounter[12]~50_combout\,
	cout => \ClkDividerN|s_divCounter[12]~51\);

-- Location: FF_X55_Y71_N31
\ClkDividerN|s_divCounter[12]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[12]~50_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(12));

-- Location: LCCOMB_X55_Y70_N0
\ClkDividerN|s_divCounter[13]~52\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[13]~52_combout\ = (\ClkDividerN|s_divCounter\(13) & (!\ClkDividerN|s_divCounter[12]~51\)) # (!\ClkDividerN|s_divCounter\(13) & ((\ClkDividerN|s_divCounter[12]~51\) # (GND)))
-- \ClkDividerN|s_divCounter[13]~53\ = CARRY((!\ClkDividerN|s_divCounter[12]~51\) # (!\ClkDividerN|s_divCounter\(13)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0101101001011111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(13),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[12]~51\,
	combout => \ClkDividerN|s_divCounter[13]~52_combout\,
	cout => \ClkDividerN|s_divCounter[13]~53\);

-- Location: FF_X56_Y71_N15
\ClkDividerN|s_divCounter[13]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	asdata => \ClkDividerN|s_divCounter[13]~52_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(13));

-- Location: LCCOMB_X55_Y70_N2
\ClkDividerN|s_divCounter[14]~54\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[14]~54_combout\ = (\ClkDividerN|s_divCounter\(14) & (\ClkDividerN|s_divCounter[13]~53\ $ (GND))) # (!\ClkDividerN|s_divCounter\(14) & (!\ClkDividerN|s_divCounter[13]~53\ & VCC))
-- \ClkDividerN|s_divCounter[14]~55\ = CARRY((\ClkDividerN|s_divCounter\(14) & !\ClkDividerN|s_divCounter[13]~53\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100001100001100",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \ClkDividerN|s_divCounter\(14),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[13]~53\,
	combout => \ClkDividerN|s_divCounter[14]~54_combout\,
	cout => \ClkDividerN|s_divCounter[14]~55\);

-- Location: FF_X56_Y71_N27
\ClkDividerN|s_divCounter[14]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	asdata => \ClkDividerN|s_divCounter[14]~54_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(14));

-- Location: LCCOMB_X55_Y70_N4
\ClkDividerN|s_divCounter[15]~56\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[15]~56_combout\ = (\ClkDividerN|s_divCounter\(15) & (!\ClkDividerN|s_divCounter[14]~55\)) # (!\ClkDividerN|s_divCounter\(15) & ((\ClkDividerN|s_divCounter[14]~55\) # (GND)))
-- \ClkDividerN|s_divCounter[15]~57\ = CARRY((!\ClkDividerN|s_divCounter[14]~55\) # (!\ClkDividerN|s_divCounter\(15)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \ClkDividerN|s_divCounter\(15),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[14]~55\,
	combout => \ClkDividerN|s_divCounter[15]~56_combout\,
	cout => \ClkDividerN|s_divCounter[15]~57\);

-- Location: FF_X56_Y71_N9
\ClkDividerN|s_divCounter[15]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	asdata => \ClkDividerN|s_divCounter[15]~56_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	sload => VCC,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(15));

-- Location: LCCOMB_X55_Y70_N6
\ClkDividerN|s_divCounter[16]~58\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[16]~58_combout\ = (\ClkDividerN|s_divCounter\(16) & (\ClkDividerN|s_divCounter[15]~57\ $ (GND))) # (!\ClkDividerN|s_divCounter\(16) & (!\ClkDividerN|s_divCounter[15]~57\ & VCC))
-- \ClkDividerN|s_divCounter[16]~59\ = CARRY((\ClkDividerN|s_divCounter\(16) & !\ClkDividerN|s_divCounter[15]~57\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(16),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[15]~57\,
	combout => \ClkDividerN|s_divCounter[16]~58_combout\,
	cout => \ClkDividerN|s_divCounter[16]~59\);

-- Location: FF_X55_Y70_N7
\ClkDividerN|s_divCounter[16]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[16]~58_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(16));

-- Location: LCCOMB_X55_Y70_N8
\ClkDividerN|s_divCounter[17]~60\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[17]~60_combout\ = (\ClkDividerN|s_divCounter\(17) & (!\ClkDividerN|s_divCounter[16]~59\)) # (!\ClkDividerN|s_divCounter\(17) & ((\ClkDividerN|s_divCounter[16]~59\) # (GND)))
-- \ClkDividerN|s_divCounter[17]~61\ = CARRY((!\ClkDividerN|s_divCounter[16]~59\) # (!\ClkDividerN|s_divCounter\(17)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011110000111111",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datab => \ClkDividerN|s_divCounter\(17),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[16]~59\,
	combout => \ClkDividerN|s_divCounter[17]~60_combout\,
	cout => \ClkDividerN|s_divCounter[17]~61\);

-- Location: FF_X55_Y70_N9
\ClkDividerN|s_divCounter[17]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[17]~60_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(17));

-- Location: LCCOMB_X55_Y70_N10
\ClkDividerN|s_divCounter[18]~62\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[18]~62_combout\ = (\ClkDividerN|s_divCounter\(18) & (\ClkDividerN|s_divCounter[17]~61\ $ (GND))) # (!\ClkDividerN|s_divCounter\(18) & (!\ClkDividerN|s_divCounter[17]~61\ & VCC))
-- \ClkDividerN|s_divCounter[18]~63\ = CARRY((\ClkDividerN|s_divCounter\(18) & !\ClkDividerN|s_divCounter[17]~61\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1010010100001010",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(18),
	datad => VCC,
	cin => \ClkDividerN|s_divCounter[17]~61\,
	combout => \ClkDividerN|s_divCounter[18]~62_combout\,
	cout => \ClkDividerN|s_divCounter[18]~63\);

-- Location: FF_X55_Y70_N11
\ClkDividerN|s_divCounter[18]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[18]~62_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(18));

-- Location: FF_X55_Y70_N13
\ClkDividerN|s_divCounter[19]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[19]~64_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(19));

-- Location: LCCOMB_X55_Y70_N30
\ClkDividerN|clkOut~4\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|clkOut~4_combout\ = (\ClkDividerN|s_divCounter\(19) & (\ClkDividerN|s_divCounter\(22) & (\ClkDividerN|s_divCounter\(20) & \ClkDividerN|s_divCounter\(21))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(19),
	datab => \ClkDividerN|s_divCounter\(22),
	datac => \ClkDividerN|s_divCounter\(20),
	datad => \ClkDividerN|s_divCounter\(21),
	combout => \ClkDividerN|clkOut~4_combout\);

-- Location: LCCOMB_X55_Y70_N24
\ClkDividerN|s_divCounter[25]~76\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|s_divCounter[25]~76_combout\ = \ClkDividerN|s_divCounter[24]~75\ $ (\ClkDividerN|s_divCounter\(25))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000111111110000",
	sum_lutc_input => "cin")
-- pragma translate_on
PORT MAP (
	datad => \ClkDividerN|s_divCounter\(25),
	cin => \ClkDividerN|s_divCounter[24]~75\,
	combout => \ClkDividerN|s_divCounter[25]~76_combout\);

-- Location: FF_X55_Y70_N25
\ClkDividerN|s_divCounter[25]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|s_divCounter[25]~76_combout\,
	sclr => \ClkDividerN|LessThan0~6_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|s_divCounter\(25));

-- Location: LCCOMB_X55_Y70_N28
\ClkDividerN|LessThan0~4\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|LessThan0~4_combout\ = ((!\ClkDividerN|s_divCounter\(17) & !\ClkDividerN|s_divCounter\(18))) # (!\ClkDividerN|s_divCounter\(23))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011001100111111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \ClkDividerN|s_divCounter\(23),
	datac => \ClkDividerN|s_divCounter\(17),
	datad => \ClkDividerN|s_divCounter\(18),
	combout => \ClkDividerN|LessThan0~4_combout\);

-- Location: LCCOMB_X56_Y71_N20
\ClkDividerN|LessThan0~5\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|LessThan0~5_combout\ = ((!\ClkDividerN|s_divCounter\(24) & ((\ClkDividerN|LessThan0~4_combout\) # (!\ClkDividerN|clkOut~4_combout\)))) # (!\ClkDividerN|s_divCounter\(25))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0011111100011111",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|clkOut~4_combout\,
	datab => \ClkDividerN|s_divCounter\(24),
	datac => \ClkDividerN|s_divCounter\(25),
	datad => \ClkDividerN|LessThan0~4_combout\,
	combout => \ClkDividerN|LessThan0~5_combout\);

-- Location: LCCOMB_X56_Y71_N14
\ClkDividerN|clkOut~2\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|clkOut~2_combout\ = (\ClkDividerN|s_divCounter\(14) & (!\ClkDividerN|s_divCounter\(6) & (\ClkDividerN|s_divCounter\(13) & \ClkDividerN|s_divCounter\(12))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0010000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(14),
	datab => \ClkDividerN|s_divCounter\(6),
	datac => \ClkDividerN|s_divCounter\(13),
	datad => \ClkDividerN|s_divCounter\(12),
	combout => \ClkDividerN|clkOut~2_combout\);

-- Location: LCCOMB_X56_Y71_N24
\ClkDividerN|clkOut~5\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|clkOut~5_combout\ = (!\ClkDividerN|s_divCounter\(15) & (\ClkDividerN|s_divCounter\(11) & (\ClkDividerN|s_divCounter\(16) & !\ClkDividerN|s_divCounter\(17))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000000001000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(15),
	datab => \ClkDividerN|s_divCounter\(11),
	datac => \ClkDividerN|s_divCounter\(16),
	datad => \ClkDividerN|s_divCounter\(17),
	combout => \ClkDividerN|clkOut~5_combout\);

-- Location: LCCOMB_X56_Y71_N28
\ClkDividerN|clkOut~6\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|clkOut~6_combout\ = (\ClkDividerN|s_divCounter\(24) & (!\ClkDividerN|s_divCounter\(23) & (!\ClkDividerN|s_divCounter\(25) & \ClkDividerN|clkOut~5_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "0000001000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|s_divCounter\(24),
	datab => \ClkDividerN|s_divCounter\(23),
	datac => \ClkDividerN|s_divCounter\(25),
	datad => \ClkDividerN|clkOut~5_combout\,
	combout => \ClkDividerN|clkOut~6_combout\);

-- Location: LCCOMB_X56_Y71_N12
\ClkDividerN|clkOut~7\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|clkOut~7_combout\ = (\ClkDividerN|clkOut~4_combout\ & (\ClkDividerN|s_divCounter\(18) & (\ClkDividerN|clkOut~3_combout\ & \ClkDividerN|clkOut~6_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1000000000000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|clkOut~4_combout\,
	datab => \ClkDividerN|s_divCounter\(18),
	datac => \ClkDividerN|clkOut~3_combout\,
	datad => \ClkDividerN|clkOut~6_combout\,
	combout => \ClkDividerN|clkOut~7_combout\);

-- Location: LCCOMB_X56_Y71_N4
\ClkDividerN|clkOut~8\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|clkOut~8_combout\ = (\ClkDividerN|clkOut~q\) # ((\ClkDividerN|clkOut~1_combout\ & (\ClkDividerN|clkOut~2_combout\ & \ClkDividerN|clkOut~7_combout\)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111100011110000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|clkOut~1_combout\,
	datab => \ClkDividerN|clkOut~2_combout\,
	datac => \ClkDividerN|clkOut~q\,
	datad => \ClkDividerN|clkOut~7_combout\,
	combout => \ClkDividerN|clkOut~8_combout\);

-- Location: LCCOMB_X56_Y71_N22
\ClkDividerN|clkOut~9\ : cycloneive_lcell_comb
-- Equation(s):
-- \ClkDividerN|clkOut~9_combout\ = (\ClkDividerN|clkOut~8_combout\ & ((\ClkDividerN|LessThan0~5_combout\) # ((\ClkDividerN|LessThan0~3_combout\) # (\ClkDividerN|LessThan0~1_combout\))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111000011100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \ClkDividerN|LessThan0~5_combout\,
	datab => \ClkDividerN|LessThan0~3_combout\,
	datac => \ClkDividerN|clkOut~8_combout\,
	datad => \ClkDividerN|LessThan0~1_combout\,
	combout => \ClkDividerN|clkOut~9_combout\);

-- Location: FF_X56_Y71_N23
\ClkDividerN|clkOut\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \CLOCK_50~inputclkctrl_outclk\,
	d => \ClkDividerN|clkOut~9_combout\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \ClkDividerN|clkOut~q\);

-- Location: CLKCTRL_G14
\ClkDividerN|clkOut~clkctrl\ : cycloneive_clkctrl
-- pragma translate_off
GENERIC MAP (
	clock_type => "global clock",
	ena_register_mode => "none")
-- pragma translate_on
PORT MAP (
	inclk => \ClkDividerN|clkOut~clkctrl_INCLK_bus\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	outclk => \ClkDividerN|clkOut~clkctrl_outclk\);

-- Location: IOIBUF_X115_Y17_N1
\SW[0]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SW(0),
	o => \SW[0]~input_o\);

-- Location: IOIBUF_X115_Y14_N1
\SW[1]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SW(1),
	o => \SW[1]~input_o\);

-- Location: LCCOMB_X91_Y69_N2
\system|aux~7\ : cycloneive_lcell_comb
-- Equation(s):
-- \system|aux~7_combout\ = (\SW[1]~input_o\ & ((\system|aux\(6)))) # (!\SW[1]~input_o\ & (\SW[0]~input_o\))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111110000001100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \SW[0]~input_o\,
	datac => \SW[1]~input_o\,
	datad => \system|aux\(6),
	combout => \system|aux~7_combout\);

-- Location: IOIBUF_X115_Y15_N8
\SW[2]~input\ : cycloneive_io_ibuf
-- pragma translate_off
GENERIC MAP (
	bus_hold => "false",
	simulate_z_as => "z")
-- pragma translate_on
PORT MAP (
	i => ww_SW(2),
	o => \SW[2]~input_o\);

-- Location: FF_X91_Y69_N3
\system|aux[7]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ClkDividerN|clkOut~clkctrl_outclk\,
	d => \system|aux~7_combout\,
	ena => \SW[2]~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \system|aux\(7));

-- Location: LCCOMB_X91_Y69_N16
\system|aux~6\ : cycloneive_lcell_comb
-- Equation(s):
-- \system|aux~6_combout\ = (\SW[1]~input_o\ & ((\system|aux\(5)))) # (!\SW[1]~input_o\ & (\system|aux\(7)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110111001000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SW[1]~input_o\,
	datab => \system|aux\(7),
	datad => \system|aux\(5),
	combout => \system|aux~6_combout\);

-- Location: FF_X91_Y69_N17
\system|aux[6]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ClkDividerN|clkOut~clkctrl_outclk\,
	d => \system|aux~6_combout\,
	ena => \SW[2]~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \system|aux\(6));

-- Location: LCCOMB_X91_Y69_N10
\system|aux~5\ : cycloneive_lcell_comb
-- Equation(s):
-- \system|aux~5_combout\ = (\SW[1]~input_o\ & ((\system|aux\(4)))) # (!\SW[1]~input_o\ & (\system|aux\(6)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1110111001000100",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SW[1]~input_o\,
	datab => \system|aux\(6),
	datad => \system|aux\(4),
	combout => \system|aux~5_combout\);

-- Location: FF_X91_Y69_N11
\system|aux[5]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ClkDividerN|clkOut~clkctrl_outclk\,
	d => \system|aux~5_combout\,
	ena => \SW[2]~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \system|aux\(5));

-- Location: LCCOMB_X91_Y69_N28
\system|aux~4\ : cycloneive_lcell_comb
-- Equation(s):
-- \system|aux~4_combout\ = (\SW[1]~input_o\ & ((\system|aux\(3)))) # (!\SW[1]~input_o\ & (\system|aux\(5)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111101000001010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \system|aux\(5),
	datac => \SW[1]~input_o\,
	datad => \system|aux\(3),
	combout => \system|aux~4_combout\);

-- Location: FF_X91_Y69_N29
\system|aux[4]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ClkDividerN|clkOut~clkctrl_outclk\,
	d => \system|aux~4_combout\,
	ena => \SW[2]~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \system|aux\(4));

-- Location: LCCOMB_X91_Y69_N6
\system|aux~3\ : cycloneive_lcell_comb
-- Equation(s):
-- \system|aux~3_combout\ = (\SW[1]~input_o\ & ((\system|aux\(2)))) # (!\SW[1]~input_o\ & (\system|aux\(4)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111101001010000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SW[1]~input_o\,
	datac => \system|aux\(4),
	datad => \system|aux\(2),
	combout => \system|aux~3_combout\);

-- Location: FF_X91_Y69_N7
\system|aux[3]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ClkDividerN|clkOut~clkctrl_outclk\,
	d => \system|aux~3_combout\,
	ena => \SW[2]~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \system|aux\(3));

-- Location: LCCOMB_X91_Y69_N20
\system|aux~2\ : cycloneive_lcell_comb
-- Equation(s):
-- \system|aux~2_combout\ = (\SW[1]~input_o\ & ((\system|aux\(1)))) # (!\SW[1]~input_o\ & (\system|aux\(3)))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111101000001010",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \system|aux\(3),
	datac => \SW[1]~input_o\,
	datad => \system|aux\(1),
	combout => \system|aux~2_combout\);

-- Location: FF_X91_Y69_N21
\system|aux[2]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ClkDividerN|clkOut~clkctrl_outclk\,
	d => \system|aux~2_combout\,
	ena => \SW[2]~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \system|aux\(2));

-- Location: LCCOMB_X91_Y69_N18
\system|aux~1\ : cycloneive_lcell_comb
-- Equation(s):
-- \system|aux~1_combout\ = (\SW[1]~input_o\ & (\system|aux\(0))) # (!\SW[1]~input_o\ & ((\system|aux\(2))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1111010110100000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	dataa => \SW[1]~input_o\,
	datac => \system|aux\(0),
	datad => \system|aux\(2),
	combout => \system|aux~1_combout\);

-- Location: FF_X91_Y69_N19
\system|aux[1]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ClkDividerN|clkOut~clkctrl_outclk\,
	d => \system|aux~1_combout\,
	ena => \SW[2]~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \system|aux\(1));

-- Location: LCCOMB_X91_Y69_N8
\system|aux~0\ : cycloneive_lcell_comb
-- Equation(s):
-- \system|aux~0_combout\ = (\SW[1]~input_o\ & (\SW[0]~input_o\)) # (!\SW[1]~input_o\ & ((\system|aux\(1))))

-- pragma translate_off
GENERIC MAP (
	lut_mask => "1100111111000000",
	sum_lutc_input => "datac")
-- pragma translate_on
PORT MAP (
	datab => \SW[0]~input_o\,
	datac => \SW[1]~input_o\,
	datad => \system|aux\(1),
	combout => \system|aux~0_combout\);

-- Location: FF_X91_Y69_N9
\system|aux[0]\ : dffeas
-- pragma translate_off
GENERIC MAP (
	is_wysiwyg => "true",
	power_up => "low")
-- pragma translate_on
PORT MAP (
	clk => \ClkDividerN|clkOut~clkctrl_outclk\,
	d => \system|aux~0_combout\,
	ena => \SW[2]~input_o\,
	devclrn => ww_devclrn,
	devpor => ww_devpor,
	q => \system|aux\(0));

ww_LEDR(0) <= \LEDR[0]~output_o\;

ww_LEDR(1) <= \LEDR[1]~output_o\;

ww_LEDR(2) <= \LEDR[2]~output_o\;

ww_LEDR(3) <= \LEDR[3]~output_o\;

ww_LEDR(4) <= \LEDR[4]~output_o\;

ww_LEDR(5) <= \LEDR[5]~output_o\;

ww_LEDR(6) <= \LEDR[6]~output_o\;

ww_LEDR(7) <= \LEDR[7]~output_o\;
END structure;


