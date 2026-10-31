library IEEE;
use IEEE.std_logic_1164.all;

entity Dec2_4EnDemo is
	port(SW : in std_logic_vector(1 downto 0);
		  KEY : in std_logic_vector (0 downto 0);
		  LEDR :out std_logic_vector(3 downto 0));
end Dec2_4EnDemo;
		
architecture Shell of Dec2_4EnDemo is
begin
Dec2_4En_0 : entity work.Dec2_4En(BehavEquations)
port map ( inputs   => SW,
			  enable   => KEY(0),
			  outputs => LEDR);
end shell;
