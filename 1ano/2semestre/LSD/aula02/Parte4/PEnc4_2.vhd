library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity PEnc4_2 is 
	port ( I	 : in std_logic_vector(3 downto 0);
			 O : out std_logic_vector(1 downto 0);
			 validOut : out std_logic);
end PEnc4_2;


architecture BehavAssign of PEnc4_2 is

begin
	process(I) 
	begin
		if I(3) = '1' then
				O <= "11";
		elsif I(2) = '1' then 
				O <= "10";
		elsif I(1) = '1' then
				O <= "01";
		else 
				O <= "00";
		end if;
	end process;
	validOut <= '0' when I = "0000" else '1';
end BehavAssign;
			