#include <iostream>
#include <fstream>

namespace Program {
    class Note {
    private:
        std::string _name;
        std::string _content;
    public:
        std::string GetName() {
            return _name;
        }

        std::string GetContent() {
            return _content;
        }

        Note(std::string& name, std::string& content): _name(name), _content(content) {};
    };

    class Vault {
    public:
        static std::string GetNoteContent(const std::string& name, const std::string& file) {
            std::string res;
            std::string str;
            std::ifstream in(file);
            while(std::getline(in, str)){
                if (str == name){
                    while (std::getline(in, str)){
                        if (str[0] == '\t'){
                            str.erase(0, 1);
                            res += str + '\n';
                        }
                        else{
                            str.pop_back();
                            break;
                        }
                    }
                    break;
                }
            }
            in.close();
            return res;
        }

        static void CreateNote(Note& note, const std::string& file) {
            std::string name = note.GetName();
            std::string content = note.GetContent();
            std::ofstream out(file, std::ios::app);
            out << '\n' << name << '\n' << '\t' << Vault::Replace(content, "\n", "\n\t");
        }

        static std::string Replace(const std::string& str, const std::string& old_str, const std::string& new_str) {
            std::string res = str;
            size_t len = old_str.size();
            for(size_t i = 0; i < res.size(); ++i){
                if (res.substr(i, len) == old_str){
                    res.replace(i, len, new_str);
                    i += new_str.size() - 1;
                }
            }
            return res;
        }
    };
}