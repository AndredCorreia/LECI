library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity XmasController is
    Port (
        CLK    : in  STD_LOGIC;
        SW     : in  STD_LOGIC_VECTOR(1 downto 0);
        HEX0   : out STD_LOGIC_VECTOR(6 downto 0)
    );
end XmasController;

architecture structure of XmasController is
    signal program_number : integer range 0 to 3;
	 

	 
begin
    process(SW)
    begin
        case SW is
            when "00" =>
                program_number <= 0;
            when "01" =>
                program_number <= 1;
            when "10" =>
                program_number <= 2;
            when "11" =>
                program_number <= 3;
            when others =>
                program_number <= 0;
        end case;
    end process;

	 Programa1_inst : if program_number= 1 generate
        Programa1_comp : entity work.Programa1
            port map (
                CLK => CLK
            );
    end generate;

    Program2_inst : if program_number= 2 generate
        Program2_comp : entity work.Program2
            port map (
                CLK => CLK
            );
    end generate;
	 Programa3_inst : if program_number= 3 generate
        Programa3_comp : entity work.Programa3
            port map (
                CLK => CLK
            );
    end generate;
	 Programa4_inst : if program_number= 4 generate
        Programa4_comp : entity work.Programa4
            port map (
                CLK => CLK
            );
    end generate;
	 
	 
	 
    process(program_number)
    begin
        case program_number is
            when 0 =>
                HEX0 <= "1000000";
            when 1 =>
                HEX0 <= "1111001";
            when 2 =>
                HEX0 <= "0100100";
            when 3 =>
                HEX0 <= "0110000";
            when others =>
                HEX0 <= "1111111";
        end case;
    end process;

end structure;
