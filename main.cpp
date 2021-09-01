#include <iostream>
#include <served/served.hpp>
using namespace std;

string nome;
class Classevazia {     // The class
public:
    string minPrice;
    string model;
    int year;
};

int main(int argc, const char *argv[])
{
    served::multiplexer mux;
    mux.handle("/api/{id}")
            .post([&](served::response &res, const served::request &req) {
                string name = req.params["id"];
                try {
                    nome = name;
                    res.set_header("content-type", "application/json");
                    res << "{ \"content\": \"novo nome criado: " << nome << "!\" }\n";
                } catch (string e) {
                    res << "{ \"content\": \"erro: " << e << "!\" }\n";
                }
            })
            .get([&](served::response &res, const served::request &req) {
                res.set_header("content-type", "application/json");
                res << "{ \"content\": \"o nome é , " << nome << "!\" }\n";
            })
            .put([&](served::response &res, const served::request &req) {
                string name = req.params["id"];
                res.set_header("content-type", "application/json");
                if (name.length() > 0) {
                    nome = name;
                    res << "{ \"content\": \"o nome agora é " << name << "!\" }\n";
                } else {
                    res << "{ \"content\": \"Nome não criado" << "!\" }\n";
                }
             })
             .del([&](served::response &res, const served::request &req) {
                 nome = "";
                 res.set_header("content-type", "application/json");
                 if (nome == "") {
                     res << "{ \"content\": \"o nome agora é " << nome << "!\" }\n";
                 } else {
                     res << "{ \"content\": \"Nome não criado" << "!\" }\n";
                 }
             });

    cout << " server rodando:127.0.0.1, 3000" << endl;

    served::net::server server("127.0.0.1", "3000", mux);
    server.run(10);

    return (EXIT_SUCCESS);
}