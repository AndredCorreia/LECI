library IEEE;
use IEEE.std_logic_1164.all;

entity Mux2_1 is

	port (sel : in std_logic;
			A,B : in std_logic_vector(1 downto 0);
			outport : out std_logic_vector (1 downto 0));
			
end Mux2_1;

architecture BehavAssign of Mux2_1 is
begin
	outport <= A when sel = '0' else B;
end BehavAssign;
