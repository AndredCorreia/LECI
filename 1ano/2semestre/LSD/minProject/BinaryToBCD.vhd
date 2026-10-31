library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.NUMERIC_STD.all;

entity BinaryToBCD is
    port (
        binary_input              : in  std_logic_vector(3 downto 0);
        bcd_output1, bcd_output2  : out std_logic_vector(3 downto 0)
    );
end entity BinaryToBCD;

architecture Behavioral of BinaryToBCD is
    signal quotient, remainder, ten : unsigned (3 downto 0);
begin
    ten       <= to_unsigned(10, 4);
    quotient  <= unsigned(binary_input) / ten;
    remainder <= unsigned(binary_input) rem ten;
  
    bcd_output1 <= std_logic_vector(remainder);
    bcd_output2 <= std_logic_vector(quotient);
end architecture Behavioral;
