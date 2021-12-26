#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>

static int gerRegOrVal(const std::unordered_map<std::string, int>& registers, std::string regOrVal)
{
    return isalpha(regOrVal[0]) ? registers.at(regOrVal) : std::stoi(regOrVal);
}

static std::vector<std::string> tokenize(std::string const& str)
{
    std::string token;
    std::vector<std::string> result;
    result.reserve(3);
    std::stringstream stringstream(str, std::istringstream::in);

    while (stringstream >> token)
    {
        result.push_back(token);
    }

    return result;
}

std::unordered_map<std::string, int> assembler(const std::vector<std::string>& assembly)
{
    std::unordered_map<std::string, int> registers;

    for (unsigned i = 0; i < assembly.size(); ++i)
    {
        std::vector<std::string> instruction = tokenize(assembly[i]);

        if (instruction[0] == "mov")
        {
            registers[instruction[1]] = gerRegOrVal(registers, instruction[2]);
        }
        else if (instruction[0] == "inc")
        {
            registers[instruction[1]]++;
        }
        else if (instruction[0] == "dec")
        {
            registers[instruction[1]]--;
        }
        else if (instruction[0] == "jnz" && gerRegOrVal(registers, instruction[1]))
        {
            i += (gerRegOrVal(registers, instruction[2]) - 1);
        }
    }

    return registers;
}

int main()
{
    std::vector<std::string> program{ "mov a 5", "inc a", "dec a", "dec a",
                                      "jnz a -1", "inc a" };
    std::unordered_map<std::string, int> out{ { "a", 1 } };

    auto test = assembler(program);
    assert(gerRegOrVal(out, "a") == gerRegOrVal(test, "a"));
    return 0;
}
