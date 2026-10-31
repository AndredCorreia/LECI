library IEEE;
use IEEE.std_logic_1164.all;

entity Mux2_1Demo is

port (SW : in std_logic_vector(3 downto 0);
		Key : in std_logic_vector(0 downto 0);
		Ledr : out std_logic_vector (1 downto 0));
		end Mux2_1Demo;
		
architecture shell of Mux2_1Demo is
begin


mux2_1_0 : entity work.mux2_1(BehavAssign)

port map (sel => not Key(0),
			 A=> SW (1 downto 0),
			 B => SW (3 downto 2),
			 outport =>LEDR);
			 end shell;
			 
			