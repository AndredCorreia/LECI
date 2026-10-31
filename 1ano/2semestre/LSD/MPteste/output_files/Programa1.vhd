library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity Programa1 is
    Port ( LEDR : out STD_LOGIC_VECTOR(3 downto 0);
			  CLK    : in  STD_LOGIC;            
			  LEDG : out STD_LOGIC_VECTOR(3 downto 0));
end Programa1;

architecture Behavioral of Programa1 is
begin
    process
    begin
        LEDR <= (others => '1'); 
        LEDG <= (others => '1'); 
    
	 end process;
end Behavioral;