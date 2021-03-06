/* Authors: Aaron Graham (aaron.graham@unb.ca, aarongraham9@gmail.com),
 *           Jean-Philippe Legault (jlegault@unb.ca, jeanphilippe.legault@gmail.com) and
 *            Dr. Kenneth B. Kent (ken@unb.ca)
 *            for the Reconfigurable Computing Research Lab at the
 *             Univerity of New Brunswick in Fredericton, New Brunswick, Canada
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "rtl_int.hpp"
#include "rtl_utils.hpp"

#define bad_ops(test) _bad_ops(test, __func__, __LINE__)
inline static std::string _bad_ops(const std::string& test, const char *FUNCT, int LINE)	
{	
	std::cerr << "INVALID INPUT OPS: (" << test << ")@" << FUNCT << "::" << std::to_string(LINE) << std::endl;	
	std::abort();
}

/***
 *     __   __       ___  __   __           ___       __       
 *    /  ` /  \ |\ |  |  |__) /  \ |       |__  |    /  \ |  | 
 *    \__, \__/ | \|  |  |  \ \__/ |___    |    |___ \__/ |/\| 
 *                                                             
 * 	This is used for testing purposes only, unused in ODIN as the input is already preprocessed
 */

static std::string arithmetic(const std::string& op, const std::string& a_in)
{

	VNumber a(a_in);


	/* return Process Operator via ternary */
	return (
		(op == "to_unsigned")?	V_UNSIGNED(a):
		(op == "to_signed")	 ?	V_SIGNED(a):
		(op == "~")		?		V_BITWISE_NOT(a):
		(op == "-")		?		V_MINUS(a):
		(op == "+")		?		V_ADD(a):
		(op == "&")		?		V_BITWISE_AND(a):
		(op == "|")		?		V_BITWISE_OR(a):
		(op == "^")		?		V_BITWISE_XOR(a):
		(op == "~&")	?		V_BITWISE_NAND(a):
		(op == "~|")	?		V_BITWISE_NOR(a):
		(op == "~^"	
		|| op == "^~")	?		V_BITWISE_XNOR(a):
		(op == "!")		?		V_LOGICAL_NOT(a):
								bad_ops(op)
	).to_full_string();
}

static std::string arithmetic(const std::string& a_in, const std::string& op, const std::string& b_in)
{

	VNumber a(a_in);
	VNumber b(b_in);


	/* return Process Operator via ternary */
	return (
		(op == "&")		?		V_BITWISE_AND(a, b):
		(op == "|")		?		V_BITWISE_OR(a, b):
		(op == "^")		?		V_BITWISE_XOR(a, b):
		(op == "~&")	?		V_BITWISE_NAND(a, b):
		(op == "~|")	?		V_BITWISE_NOR(a, b):
		(op == "~^"	
		|| op == "^~")	?		V_BITWISE_XNOR(a, b):
		/*	Case test	*/
		(op == "===" )	?		V_CASE_EQUAL(a, b):
		(op == "!==")	?		V_CASE_NOT_EQUAL(a, b):
		/*	Shift Operator	*/
		(op == "<<")	?		V_SHIFT_LEFT(a, b):
		(op == "<<<")	?		V_SIGNED_SHIFT_LEFT(a, b):
		(op == ">>")	?		V_SHIFT_RIGHT(a, b):
		(op == ">>>")	?		V_SIGNED_SHIFT_RIGHT(a, b):
		/* Logical Operators */
		(op == "&&")	?		V_LOGICAL_AND(a, b):
		(op == "||")	?		V_LOGICAL_OR(a, b):
		(op == "<")		?		V_LT(a, b):																																													
		(op == ">")		?		V_GT(a, b):
		(op == "<=")	?		V_LE(a, b):
		(op == ">=")	?		V_GE(a, b):
		(op == "==")	?		V_EQUAL(a, b):
		(op == "!=")	?		V_NOT_EQUAL(a, b):
		/* arithmetic Operators */																
		(op == "+")		?		V_ADD(a, b):
		(op == "-")		?		V_MINUS(a, b):
		(op == "*")		?		V_MULTIPLY(a, b):
		(op == "**")	?		V_POWER(a, b):
		/* cannot div by 0 */
		(op == "/")		?		V_DIV(a, b):
		(op == "%")		?		V_MOD(a, b):
								bad_ops(op)
	).to_full_string();
}

int main(int argc, char** argv) 
{
	std::vector<std::string> input;
	input.reserve(argc);
for(int i=0; i < argc; i++)		input.push_back(argv[i]);

	std::string result;

	if(argc < 3)
	{
		ERR_MSG("Not Enough Arguments: " << std::to_string(argc - 1));

		return -1;
	}
	else if(argc == 3 && input[1] == "is_true")
	{
		VNumber input_2(input[2]);

		result = (V_TRUE(input_2) ? "pass" : "fail");
	}
	else if(argc == 3 && input[1] == "is_false")
	{
		VNumber input_2(input[2]);

		result = (V_FALSE(input_2) ? "pass" : "fail");
	}
	else if(argc == 3 && input[1] == "is_unk")
	{
		VNumber input_2(input[2]);

		result = (V_UNK(input_2) ? "pass" : "fail");
	}
	else if(argc == 3 && input[1] == "is_x")
	{
		VNumber input_2(input[2]);

		result = (V_IS_X(input_2) ? "pass" : "fail");
	}
	else if(argc == 3 && input[1] == "is_z")
	{
		VNumber input_2(input[2]);

		result = (V_IS_Z(input_2) ? "pass" : "fail");
	}
	else if(argc == 3 && input[1] == "is_unsigned")
	{
		VNumber input_2(input[2]);

		result = (V_IS_UNSIGNED(input_2) ? "pass" : "fail");
	}
	else if(argc == 3 && input[1] == "is_signed")
	{
		VNumber input_2(input[2]);

		result = (V_IS_SIGNED(input_2) ? "pass" : "fail");
	}
	else if(argc == 3 && input[1] == "display")
	{
		VNumber input_2(input[2]);

		result = V_STRING(input_2);
	}
	else if(argc == 3)
	{
		result = arithmetic(input[1], input[2]);
	}
	else if(argc == 4)
	{
		result = arithmetic(input[1], input[2], input[3]);

	}
	else if(argc == 6
	&& (input[2] == "?" && input[4] == ":"))
	{
		VNumber a(input[1]);
		VNumber b(input[3]);
		VNumber c(input[5]);

		result = V_TERNARY(a, b, c).to_full_string();
	}
	else if(argc == 6
	&&(input[1] == "{" && input[3] == "," && input[5] == "}")) // the pipe symbol is a hack since our test handle uses csv.
	{
		VNumber a(input[2]);
		VNumber b(input[4]);

		result = V_CONCAT({a, b}).to_full_string();
	}
	else if(argc == 7
	&&(input[1] == "{" && input[3] == "{" && input[5] == "}" && input[6] == "}"))
	{
		VNumber n_times(input[2]);
		VNumber replicant(input[4]);

		result = V_REPLICATE(replicant, n_times).to_full_string();
	}
	else				
	{
		ERR_MSG("invalid Arguments: " << std::to_string(argc - 1));
		return -1;
	}

	std::cout << result << std::endl;

	return 0;
}
