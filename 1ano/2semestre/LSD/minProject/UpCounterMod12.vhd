library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.NUMERIC_STD.all;

entity UpCounterMod12 is
    port (
        clk          : in  std_logic;
        reset        : in  std_logic;
        enable       : in  std_logic;
        output_count : out std_logic_vector(3 downto 0)
    );
end UpCounterMod12;

architecture Behavioral of UpCounterMod12 is
    signal counter : unsigned(3 downto 0);
begin
    process(clk)
    begin
        if rising_edge(clk) and enable = '1' then
            if reset = '1' or counter = "1011" then
                counter <= (others => '0');
            else
                counter <= counter + 1;
            end if;
        end if;
    end process;
    
    output_count <= std_logic_vector(counter);
end Behavioral;
