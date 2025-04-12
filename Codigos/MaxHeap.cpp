#include <iostream>
#include <stdexcept>
#include <utility>

using namespace std;
struct Dados{
    int valor;
};

bool operator>(Dados d1, Dados d2){
    return d1.valor > d2.valor;
}

bool operator<(Dados d1, Dados d2){
    return d1.valor < d2.valor;
}

ostream& operator<<(ostream& output, const Dados& d){
    output << d.valor;
    return output;
}
class MaxHeap{
    private:
        Dados* heap;
        int capacidade;
        int tamanho;
        inline int pai(int i);
        inline int esquerdo(int i);
        inline int direito(int i);
        void corrigeDescendo(int i);
        void corrigeSubindo(int i);

    public:
        MaxHeap(int cap);
        ~MaxHeap();
        void imprime();
        Dados retiraRaiz();
        void insereDado(Dados d);
};

MaxHeap::MaxHeap(int cap) : capacidade(cap), tamanho(0){
    heap = new Dados[capacidade];
}

MaxHeap::~MaxHeap(){
    delete[] heap;
}

int MaxHeap::pai(int i){
    return (i - 1)/2;
}

int MaxHeap::esquerdo(int i){
    return (2 * i) + 1;
}

int MaxHeap::direito(int i){
    return (2 * i) + 2;
}

void MaxHeap::corrigeDescendo(int i){
    int maior = i;
    int esq = esquerdo(i);
    int dir = direito(i);

    if(esq < tamanho && heap[esq] > heap[maior]){
        maior = esq;
    }
    if(dir < tamanho && heap[dir] > heap[maior]){
        maior = dir;
    }
    if(maior != i){
        swap(heap[i], heap[maior]);
        corrigeDescendo(maior);
    }
}

void MaxHeap::corrigeSubindo(int i){
    while (i > 0 && heap[pai(i)] < heap[i]){
        swap(heap[i], heap[pai(i)]);
        i = pai(i);
    }
}

void MaxHeap::imprime(){
    if(tamanho == 0){
        cout << "Empty Heap!" << endl;
        return;
    }
    for(int i = 0; i < tamanho; i++){
        cout << heap[i] << " ";
    }
    cout << endl;
}

Dados MaxHeap::retiraRaiz(){
    if(tamanho == 0){
        throw runtime_error("Erro retirando a raiz");
    }
    Dados raiz = heap[0];
    heap[0] = heap[tamanho - 1];

    tamanho--;
    corrigeDescendo(0);
    return raiz;
}

void MaxHeap::insereDado(Dados d){
    if(tamanho == capacidade){
        throw runtime_error("Erro: Heap cheia!");
    }
    heap[tamanho] = d;
    tamanho++;
    corrigeSubindo(tamanho - 1);
}

int main(){
    int capacidade;
    Dados valores;
    char comando;

    cin >> capacidade;
    MaxHeap myHeap(capacidade);
    do {
        try{
            cin >> comando;
            switch(comando){
                case 'i':
                    cin >> valores.valor;
                    myHeap.insereDado(valores);
                    break;
                case 'r':
                    cout << myHeap.retiraRaiz() << endl;
                    break;
                case 'p':
                    myHeap.imprime();
                    break;
                case 'f':
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e){
            cout << e.what() << endl;
        }
    } while (comando != 'f');
        cout << endl;
    return 0;
}