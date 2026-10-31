library IEEE;
use IEEE.STD_LOGIC_1164.all;


entity Dec2_4En is
port (enable : in std_logic;
		  inputs : in std_logic_vector(1 downto 0);
		  outputs : out std_logic_vector(3 downto 0));
end Dec2_4En;
architecture BehavEquations of Dec2_4En is
begin
	outputs(0) <= enable and (not inputs(1)) and (not inputs(0));
	outputs(1) <= enable and (not inputs(1)) and ( inputs(0));
	outputs(2) <= enable and ( inputs(1)) and (not inputs(0));
	outputs(3) <= enable and ( inputs(1)) and ( inputs(0));
	
	
end BehavEquations;


architecture BehavAssign of Dec2_4En is
begin
	outputs <= "0000" when (enable = '0') else
	"0001" when (inputs = "00") else
	"0010" when (inputs = "01") else
	"0100" when (inputs = "10") else
	"1000";
end BehavAssign;

architecture behavProced of Dec2_4en is

begin
process (inputs,enable)

begin 
		if enable= '0' then
		outputs <= "0000";
		elsif (inputs = "00") then
		outputs <= "0001";
		elsif (inputs= "01") then 
		outputs <="0010";
		elsif (inputs = "10") then 
		outputs <= "0100";
		else 
		outputs <= "1000";
		end if;
		end process;
		
end behavProced;
	
architecture behavproced_case of dec2_4en is 

begin

		process (inputs,enable)
		begin
		if enable = '0' then 
		outputs <= "0000";
			else
			case inputs is
			when "00" => outputs <= "0001";
			when "01" => outputs <= "0010";
			when "10" => outputs <= "0100";
			when "11" => outputs <= "1000";
			end case ;
		end if;
		end process;
		
end behavproced_case;	
