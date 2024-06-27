#include <iostream>
#include <memory>

int main() 
{
    std::weak_ptr<int> weak;
    {
        auto shared = std::make_shared<int>(15);
        weak = shared;
        std::cout << *weak.lock() << std::endl;
        if (weak.expired())
			std::cout << "weak nie zyje" << std::endl;
		else
			std::cout << "weak zyje" << std::endl;
    }    
    if (weak.expired())
        std::cout << "weak nie zyje" << std::endl;
    else
        std::cout << "weak zyje" << std::endl;
    return 0;
}
