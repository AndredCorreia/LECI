library IEEE;
use IEEE.STD_LOGIC_1164.all;

entity BinToSevenSegDecoder is
    port (
        binaryInput : in  std_logic_vector(3 downto 0);
        segmentOut  : out std_logic_vector(6 downto 0);
        enable      : in  std_logic
    );
end BinToSevenSegDecoder;

architecture Behavioral of BinToSevenSegDecoder is
begin
    process(binaryInput, enable)
    begin
        if enable = '0' then
            segmentOut <= "1111111";
        else
            case binaryInput is
                when "0001" =>
                    segmentOut <= "1111001";
                when "0010" =>
                    segmentOut <= "0100100";
                when "0011" =>
                    segmentOut <= "0110000";
                when "0100" =>
                    segmentOut <= "0011001";
                when "0101" =>
                    segmentOut <= "0010010";
                when "0110" =>
                    segmentOut <= "0000010";
                when "0111" =>
                    segmentOut <= "1111000";
                when "1000" =>
                    segmentOut <= "0000000";
                when "1001" =>
                    segmentOut <= "0010000";
                when "1010" =>
                    segmentOut <= "0001000";
                when "1011" =>
                    segmentOut <= "0000011";
                when "1100" =>
                    segmentOut <= "1000110";
                when "1101" =>
                    segmentOut <= "0100001";
                when "1110" =>
                    segmentOut <= "0000110";
                when "1111" =>
                    segmentOut <= "0001110";
                when others =>
                    segmentOut <= "1000000";
            end case;
        end if;
    end process;
end Behavioral;
