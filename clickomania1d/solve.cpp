#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define USAGE "Usage: solve string.txt"
// string.txt contains EOF-terminated string with up to 150 uppercase letters

class ClickString
{
public:
    ClickString(const std::string& str)
    {
	// iterate over chars in string and represent as parallel
	// vectors of char and its counts
	for (auto iter = str.begin(); iter != str.end(); ++iter)
	{
	    if (m_chars.empty())
	    {
		m_chars.push_back(*iter);
		m_counts.push_back(1);
	    }
	    else
	    {
		if (*iter == m_chars.back())
		{
		    m_counts.back() += 1;
		}
		else
		{
		   m_chars.push_back(*iter);
		   m_counts.push_back(1);
		}
	    }
	}
    }

    
    friend std::ostream& operator<< (std::ostream& stream, const ClickString& str);

    bool IsSolvable()
    {
	if (IsSolvableFilter()) return true;
	if (IsUnsolvableFilter()) return false;
        return true;
    }

private:
    void GetClicks(std::vector<int>& legal_clicks)
    {
    }

    bool IsSolvableFilter() const // can have false negatives
    {
	return m_chars.empty() && m_counts.empty();
        // todo: check also if all counts != 1
    }
    bool IsUnsolvableFilter() const // can have false negatives
    {
	// has count 1 with char unmatched by other counts
        return false;
    }

    std::vector<char> m_chars;
    std::vector<int>  m_counts;
};

std::ostream& operator<< (std::ostream& stream, const ClickString& str)
{
    for (auto char_iter = str.m_chars.begin(); 
	char_iter != str.m_chars.end(); ++char_iter)
    {
	stream << *char_iter << ' ';
    }
    stream << std::endl;
    for (auto count_iter = str.m_counts.begin(); 
	count_iter != str.m_counts.end(); ++count_iter)
    {
	stream << *count_iter << ' ';
    }
    return stream;
}

int main(int argc, char** argv)
{
    if (argc != 2)
	std::cerr << USAGE << std::endl;

    // slurp input file to string
    std::ifstream ifs(argv[1]);
    std::string content;
    std::getline(ifs, content);

    // TODO: verify string assumptions (uppercase & len < 150)

    // log
    std::cout << content.length() << "|" << content << "|" << std::endl;
    ClickString clk_str(content);
    std::cout << clk_str << std::endl;

    if (clk_str.IsSolvable())
	std::cout << "solvable" << std::endl;
    else
	std::cout << "unsolvable" << std::endl;

    return 0;
}
