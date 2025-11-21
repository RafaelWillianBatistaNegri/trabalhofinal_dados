#include <iostream>
#include <list>
#include <algorithm>

using namespace std;

struct Paciente {
    string senha; 
    char prioridade;
    int hora, minuto; 
};

int horario(int hora, int minuto) {
    return hora*60 + minuto;
}

int main() {
    list<Paciente> filaV, filaA, filaD, filaB;

    int totalAtendidos = 0;
    int V = 0, A = 0, D = 0, B = 0;
    int pico = 0;
    int esperaMax = 0;

    char opcao;

    cout << "\n =========================== \n";
    cout << "SEJA BEM-VINDO AO SISTEMA TRIMAX DE TRIAGEM HOSPITALAR!" << endl;
    cout << " " << endl;
    cout << "-> Para incluir a chegada de um paciente, siga o seguinte formato de entrada: C <senha> <prioridade> <hora> <minuto>" << endl;
    cout << "-> Para atender um paciente, siga o seguinte formato: A <hora> <minuto>" << endl;
    cout << "-> Para saber o atual estado da fila de pacientes, digite 'D'" << endl;
    cout << "-> Para encerrar o atendimento do dia, digite 'Q'" << endl;
    cout << "\n =========================== \n";

    while (cin >> opcao) {
        if (opcao == 'C') {
            // Incluir pacientes na fila.
            Paciente p;
            cin >> p.senha >> p.prioridade >> p.hora >> p.minuto;

            if(p.prioridade == 'V'){
                filaV.push_back(p);
            }
            else if(p.prioridade == 'A'){
                filaA.push_back(p);
            }
            else if(p.prioridade == 'D'){
                filaD.push_back(p);
            }
            else{
                filaB.push_back(p);
            } 

            int total_pacientes = filaV.size() + filaA.size() + filaD.size() + filaB.size();
            pico = max(pico, total_pacientes);

            cout << "---> Um paciente foi adicionado a fila com sucesso!" << endl;
            cout << " \n";
        }
        else if (opcao == 'A') {
            // Realizar o atendimento.
            int h, m;
            cin >> h >> m;

            cout << h << ":" << m << " ";

            // Ninguém na fila
            if (filaV.empty() && filaA.empty() && filaD.empty() && filaB.empty()) {
                cout << "|| Sem pacientes aguardando atendimento" << endl;
                cout << " \n";
                continue;
            }

            // Adicionar na fila
            Paciente p;
            bool encontrado = true;

            if (!filaV.empty()) {
                p = filaV.front();
                filaV.pop_front();
                V++;
            }
            else if (!filaA.empty()) {
                p = filaA.front();
                filaA.pop_front();
                A++;
            }
            else if (!filaD.empty()) {
                p = filaD.front();
                filaD.pop_front();
                D++;
            }
            else if (!filaB.empty()) {
                p = filaB.front();
                filaB.pop_front();
                B++;
            }else encontrado = false;

            if (encontrado) {
                int espera = horario(h,m) - horario(p.hora, p.minuto);
                esperaMax = max(esperaMax, espera);
                totalAtendidos++;

                cout << "|| Um paciente foi atendido com sucesso!" << endl;
                cout << " \n";
            }
        }
        else if (opcao == 'D') {
            // Consultar as filas e o total de pacientes atendidos até o momento.
            cout << "\n ======================================== \n";
            cout << " \n";
            cout << "Emergencia:" << filaV.size() << " "
                 << " Urgencia:" << filaA.size() << " "
                 << " Pouco Urgente:" << filaD.size() << " "
                 << " Nao Urgente:" << filaB.size() << " "
                 << " || Total de Pacientes Atendidos:" << totalAtendidos << endl;
            cout << "\n ======================================== \n";
            cout << " \n";
        }
        else if (opcao == 'Q') {
            // Relatório dos atendimentos do dia.
            cout << " \n";
            cout << "============= RELATORIO FINAL TRIMAX =============\n";
            cout << "Total de pacientes atendidos: " << totalAtendidos << "\n";
            cout << "Pacientes atendidos por prioridade: V=" << V
                 << " A=" << A
                 << " D=" << D
                 << " B=" << B << "\n";
            cout << "Pico de lotacao: " << pico << "\n";
            cout << "Espera maxima: " << esperaMax << " min\n";
            cout << "==================================================\n";
            cout << " \n";
            cout << "---> O atendimento do dia foi finalizado com sucesso!\n";
            break;
        }
        else{
            // Default
            cout << "---> A entrada foi digitada incorretamente, por favor tente novamente!" << endl;
            cout << " \n";
            continue;
        }
    }

    return 0;
}
