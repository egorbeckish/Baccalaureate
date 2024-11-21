#include <iostream>
#include "Timer.h"
#include "Input.h"
#include "CreateMethod.h"

std::streambuf* redirectOutput(std::ofstream* fout);

int main()
{
    system("chcp 1251 > null");
    char choice;


    do {
        system("pause");
        system("cls");
        choice = getSymbol({ '1','2','3','4' },
            "1) ... 2)... 3) записать данные из txt 4) Выйти\n-> ");
        //choice = '3';
        if (choice == '4') break;
        IInputDevice method(choice);


        if (!method.isEmptyVectorString())
        {
            std::vector<std::string> exprs = method.getVectorString();
            double a = method.getLeft(), b = method.getRight();
            double eps = method.getEps();
            int N = method.getNAfterComma();


            for (int i = 0; i < exprs.size(); i++)
            {
                std::string expr = exprs[i];
                char* polStr = CreatePolStr(expr.c_str(), 0);
                if (GetError() == ERR_OK && polStr)
                {
                    Timer t;
                    Methods res(polStr, a, b, eps, expr);
                    do {
                        system("pause");
                        system("cls");
                        switch (choice)
                        {
                        case '1':
                        {
                            char method = getSymbol({ '1','2','3','4','5','6','7' },
                                "Ââåäèòå ìåòîä âû÷èñëåíèÿ ôóíêöèè:\n"
                                "Èíòåðâàëüíûå:\n1) ìåòîä äèõîòîìèè\n2) ìåòîä õîðä\n3) ìåòîä çîëîòîãî ñå÷åíèÿ\n4) êîìáèíèðîâàííûé ìåòîä\n"
                                "Èòåðàöèîííûå:\n5) ìåòîä Íüþòîíà(êàñàòåëüíûõ)\n6) ìåòîä èòåðàöèé\n\n7) âûéòè\n-> ");
                            if (method == '7') break;

                            t.reset();
                            res.setResult(choice);

                            std::cout << std::setprecision(N) << res
                                << "\nВремя на вычисление: " << t.elapsed() << std::endl;
                            continue;
                        }
                        case '2': case '3':
                        {
                            std::string filename("output.txt");
                            if (choice == '2')
                            {
                                std::cout << "Ââåäèòå èìÿ âûõîäíîãî ôàéëà:\n->";
                                getline(std::cin, filename);
                            }
                            std::ofstream* fout = new std::ofstream(filename, std::ios_base::app);
                            std::streambuf* original_cout = redirectOutput(fout);
                            if (!original_cout) break;


                            t.reset();
                            try
                            {
                                res.setResult(method.getMethod());
                                std::cout << "\n" << std::setprecision(N) << res
                                    << "Время на вычисление: " << t.elapsed()
                                    << "\nКол-во итераций: " << res.getCount() << std::endl;
                            }
                            catch (std::exception err)
                            {
                                std::cout << "\nException: " << err.what();
                            }
                            std::cout.rdbuf(original_cout);
                            fout->close();
                            choice = '4';
                        }
                        break;
                        case '4':
                            break;
                        }
                        break;
                    } while (true);
                }
                else std::cout << GetError() << std::endl;
            }
        }

    } while (choice);

    
    system("pause");
}

std::streambuf* redirectOutput(std::ofstream* fout)
{
    std::streambuf* original_cout = std::cout.rdbuf();
    while (!*fout)
    {
        std::string filename;
        char choice;
        choice = getSymbol({ '1', '2' },
            "Äàííûé ôàéë íå ìîæåò áûòü îòêðûò, ëèáî íå ñóùåñòâóåò. Ïîïðîáîâàòü åù¸ ðàç?\n1) äà\n2) âûéòè\n->");
        if (choice == '1')
        {
            std::cout << "Ââåäèòå èìÿ ôàéëà:\n->";
            getline(std::cin, filename);
        }
        else return NULL;
        fout->open(filename);
    }
    //ïåðåíàïðàâëÿåì ñòàíäàðòíûé ïîòîê âûâîäà íà ïåðåäàííûé ôàéë
    std::cout.rdbuf(fout->rdbuf());
    return original_cout;
}
