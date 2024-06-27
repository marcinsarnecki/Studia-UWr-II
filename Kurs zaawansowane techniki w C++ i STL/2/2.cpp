#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

class line_writer
{
    private:
        std::ofstream* file;
    public:
        template <typename T>
        line_writer& save (T data)
        {
            *file << data << std::endl;
            return *this;
        }

        line_writer(std::string& path)
        {
            file = new std::ofstream(path, std::ios::out);
        }

        ~line_writer()
        {
            delete file; // destruktore orstreama zamknie plik, ktory zostal otwarty
            std::cout << "Zamykam plik";
        }
};

int main()
{
    int n = 10;
    std::string path = "plik.txt";
    
    auto writer = std::make_shared<line_writer>(path);
    
    std::vector<std::shared_ptr<line_writer>> vec_pointers;
    for (int i = 0; i < n; i++)
        vec_pointers.push_back(writer);
    for (int i = 0; i < n; i++)
        vec_pointers[i]->save(i);
    return 0;
}
