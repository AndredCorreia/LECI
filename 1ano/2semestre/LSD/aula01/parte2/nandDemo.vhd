library IEEE;
use IEEE.std_logic_1164.all;

entity nandDemo is 
port (SW : in std_logic_vector (1 downto 0);
		LEDR :out std_logic_vector (0 downto 0));
		end nandDemo;


architecture shell of nandDemo is

begin


		nangatte0 : entity work.nandgate(structural)
						port map (	inport0 => SW(0),
										inport1 => SW(1),
										outport=> LEDR(0));
end shell;