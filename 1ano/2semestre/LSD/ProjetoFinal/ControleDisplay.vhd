library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity ControleDisplay is
    Port (
        display_input : in std_logic_vector(7 downto 0);
        clock : in std_logic;
        reset : in std_logic;
        HEX0 : out std_logic_vector(6 downto 0);
        HEX1 : out std_logic_vector(6 downto 0);
        HEX2 : out std_logic_vector(6 downto 0);
        HEX3 : out std_logic_vector(6 downto 0);
        HEX4 : out std_logic_vector(6 downto 0);
        HEX5 : out std_logic_vector(6 downto 0);
        HEX6 : out std_logic_vector(6 downto 0)
    );
end ControleDisplay;

architecture Behavioral of ControleDisplay is
    -- Digitos do display 7 segmentos para 0-9
    type segment_array is array(0 to 9) of std_logic_vector(6 downto 0);
    constant SEGMENTS : segment_array := (
        "1000000",  -- 0
        "1111001",  -- 1
        "0100100",  -- 2
        "0110000",  -- 3
        "0011001",  -- 4
        "0010010",  -- 5
        "0000010",  -- 6
        "1111000",  -- 7
        "0000000",  -- 8
        "0010000"   -- 9
    );

    signal digits : std_logic_vector(7 downto 0);

begin

    process(clock, reset)
    begin
        if reset = '1' then
            HEX0 <= "1111111";
            HEX1 <= "1111111";
            HEX2 <= "1111111";
            HEX3 <= "1111111";
            HEX4 <= "1111111";
            HEX5 <= "1111111";
            HEX6 <= "1111111";
        elsif rising_edge(clock) then
            digits <= display_input;
            HEX0 <= SEGMENTS(conv_integer(digits(3 downto 0)));
            HEX1 <= SEGMENTS(conv_integer(digits(7 downto 4)));
            -- Assuming the upper digits are handled similarly, you can extend this
            -- HEX2 <= SEGMENTS(conv_integer(digits(11 downto 8)));
            -- HEX3 <= SEGMENTS(conv_integer(digits(15 downto 12)));
            -- HEX4 <= SEGMENTS(conv_integer(digits(19 downto 16)));
            -- HEX5 <= SEGMENTS(conv_integer(digits(23 downto 20)));
            -- HEX6 <= SEGMENTS(conv_integer(digits(27 downto 24)));
        end if;
    end process;

end Behavioral;