#include "Huffman.h"

#define HELP_ERROR 99
#define width_unit 5

template<class T>
class Queue
{
    public:

        Queue(int d=2);
        ~Queue(void);
        void enq(T*);
        T* deq(void);
        T* front(void);
        bool empty(void) const;
        bool full(void) const;

    private:

        int back;
        T* *arr;
        int size;
        static const int SIZE=10;
        int D;
        Queue(const Queue &);
        const Queue & operator=(const Queue &);

        void reheapup(int, int);
        void reheapdown(int, int);
        void swap(T* &, T* &);

};


template<class T>
Queue<T>::Queue(int d)
{
    if(d<2) d=2;
    D=d;
    back=0;
    size=SIZE;
    arr=new T*[size];
}

template<class T>
bool Queue<T>::empty(void) const
{
    return (back<=0);
}

template<class T>
bool Queue<T>::full(void) const
{
    return (back>=size);
}

template<class T>
T* Queue<T>::deq(void)
{
    if(empty())
    {
        cerr<<"deq error! exiting..."<<endl;
        exit(1);
    }

    T* rval=arr[0];
    arr[0]=arr[back-1];
    --back;
    reheapdown(0, back-1);
    return rval;
}

template<class T>
T* Queue<T>::front(void)
{
    if(empty())
    {
        cerr<<"deq error! exiting..."<<endl;
        exit(1);
    }

    return arr[0];
}

template<class T>
void Queue<T>::enq(T* foo)
{
    if(full())
    {
        int nsize=size+SIZE;
        T* *narr=new T*[nsize];
        for(int i=0;i<size;++i)
            narr[i]=arr[i];
        delete[] arr;
        arr=narr;
        size=nsize;
    }

    arr[back++]=foo;
    reheapup(0, back-1);
}

template<class T>
void Queue<T>::reheapup(int root, int bottom)
{
    int parent;

    if(bottom > root)
    {
        parent=(bottom-1)/D;

        if(*arr[parent] > *arr[bottom])
        {
            swap(arr[parent], arr[bottom]);
            reheapup(root, parent);
        }
    }
}

template<class T>
void Queue<T>::reheapdown(int root, int bottom)
{
    int minchild, firstchild, child;

    firstchild=root*D+1;

    if(firstchild <= bottom)
    {
        minchild=firstchild;

        for(int i=2;i <= D;++i)
        {
            child=root*D+i;
            if(child <= bottom)
            {
                if(*arr[child] < *arr[minchild])
                {
                    minchild=child;
                }
            }
        }

        if(*arr[root] > *arr[minchild])
        {
            swap(arr[root], arr[minchild]);
            reheapdown(minchild, bottom);
        }
    }
}

template<class T>
void Queue<T>::swap(T* &a, T* &b)
{
    T* c;
    c=a;
    a=b;
    b=c;
}

template<class T>
Queue<T>::~Queue(void)
{
    delete[] arr;
}

class Tree
{
    private:
        class Node
        {
            public:
                unsigned int freq;
                unsigned char ch;
                Node *left, *right;
                Node(void)
                    :freq(0), ch('\0'), left(NULL), right(NULL) {}
        };

        Node *root;

        Tree(const Tree &);
        const Tree & operator=(const Tree &);
        void chop(Node * N);
        void print(ostream &, Node *, int) const;
        void print(Node *, int) const;

    public:
        Tree(void);
        ~Tree(void);
        friend ostream & operator<<(ostream &, const Tree &);
        unsigned int get_freq(void) const;
        unsigned char get_char(void) const;
        void set_freq(unsigned int);
        void set_char(unsigned char);
        Node* get_left(void) const;
        Node* get_right(void) const;
        void set_left(Node *);
        void set_right(Node *);
        Node* get_root(void) const;
        bool operator==(const Tree &) const;
        bool operator!=(const Tree &) const;
        bool operator<(const Tree &) const;
        bool operator>(const Tree &) const;
        bool operator<=(const Tree &) const;
        bool operator>=(const Tree &) const;

        void huf(Node *, unsigned char, string, string &) const;
        void huf_list(Node *, string) const;
        bool get_huf_char(string, unsigned char &) const;
        string print_char(Node *) const;
};

Tree::Tree(void)
{
    Node* N=new Node;
    root=N;
}

void Tree::chop(Node *N)
{
    if(N)
    {
        chop(N->left);
        chop(N->right);
        delete N;
    }
}

Tree::~Tree(void)
{
    chop(root);
}

unsigned int Tree::get_freq(void) const
{
    return root->freq;
}

unsigned char Tree::get_char(void) const
{
    return root->ch;
}

void Tree::set_freq(unsigned int f)
{
    root->freq=f;
}

void Tree::set_char(unsigned char c)
{
    root->ch=c;
}

Tree::Node* Tree::get_left(void) const
{
    return root->left;
}

Tree::Node* Tree::get_right(void) const
{
    return root->right;
}

void Tree::set_left(Node* N)
{
    root->left=N;
}

void Tree::set_right(Node* N)
{
    root->right=N;
}

Tree::Node* Tree::get_root(void) const
{
    return root;
}

void Tree::print(ostream & ost, Node * curr, int level) const
{
    if(curr)
    {
        print(ost,curr->right,level+1);
        ost<<setw(level*width_unit)<<print_char(curr)<<":"
           <<curr->freq<<endl;
        print(ost,curr->left,level+1);
    }
}

void Tree::print(Node * curr, int level) const
{
    if(curr)
    {
        print(curr->right,level+1);
        cout<<setw(level*width_unit)<<print_char(curr)<<":"
            <<curr->freq<<endl;
        print(curr->left,level+1);
    }
}

ostream & operator<<(ostream &ost, const Tree &t)
{
    t.print(ost, t.root, 1);
    return ost;
}


bool Tree::operator==(const Tree & T) const
{
    return (root->freq == T.root->freq);
}

bool Tree::operator!=(const Tree & T) const
{
    return (root->freq != T.root->freq);
}

bool Tree::operator<(const Tree & T) const
{
    return (root->freq < T.root->freq);
}

bool Tree::operator>(const Tree & T) const
{
    return (root->freq > T.root->freq);
}

bool Tree::operator<=(const Tree & T) const
{
    return (root->freq <= T.root->freq);
}

bool Tree::operator>=(const Tree & T) const
{
    return (root->freq >= T.root->freq);
}

void Tree::huf(Node* N, unsigned char c, string str, string & s) const
{
    if(N)
    {
        if(!N->left && !N->right && N->ch == c)
        {
            s=str;
        }
        else
        {
            huf(N->left, c, str+"0",s);
            huf(N->right, c, str+"1",s);
        }
    }
}

void Tree::huf_list(Node* N, string str) const
{
    if(N)
    	{
        if(!N->left && !N->right)
            cout<<print_char(N)<<" "<<str<<endl;
        else
        {
            huf_list(N->left, str+"0");
            huf_list(N->right, str+"1");
        }
    }
}

bool Tree::get_huf_char(string s, unsigned char & c) const
{
    Node * curr=root;
    for(unsigned int i=0;i<s.size();++i)
    {
        if(s[i]=='0')
            curr=curr->left;
        if(s[i]=='1')
            curr=curr->right;
    }

    bool found=false;

    if(!curr->left && !curr->right)
    {
        found=true;
        c=curr->ch;
    }

    return found;
}

string Tree::print_char(Node * N) const
{
    string s="";

    if(!N->left && !N->right)
    {
        unsigned char c=N->ch;

        if(iscntrl(c) || c==32)
        {

            char* cp=new char;
            for(int i=0;i<3;++i)
            {
                sprintf(cp,"%i",c%8);
                c-=c%8;
                c/=8;
                s=(*cp)+s;
            }
            s='/'+s;
        }
        else
            s=c;
    }
    return s;
}

void Huffman::esc_huf(unsigned char i, ofstream & outfile)
{
    static int bit_pos=0;
    static unsigned char c='\0';

    if(i<2)
    {
        if(i==1)
            c=c | (i<<(7-bit_pos));
        else
            c=c & static_cast<unsigned char>(255-(1<<(7-bit_pos)));
        ++bit_pos;
        bit_pos%=8;
        if(bit_pos==0)
        {
            outfile.put(c);
            c='\0';
        }
    }
    else
    {
        outfile.put(c);
    }
}

unsigned char Huffman::le_huf(ifstream & infile)
{
    static int bit_pos=0;
    static unsigned char c=infile.get();

    unsigned char i;

    i=(c>>(7-bit_pos))%2;
    ++bit_pos;
    bit_pos%=8;
    if(bit_pos==0){
        if(!infile.eof())
        {
            c=infile.get();
        }
        else
            i=2;
    }
    return i;
}

//Compressor de Huffman
void Huffman::comprimir(string ifile, string ofile, bool verbose)
{
    ifstream infile(ifile.c_str(), ios::in|ios::binary);

    //abre o ficheiro de output
    ofstream outfile(ofile.c_str(), ios::out|ios::binary);

    unsigned int f[256];
    for(int i=0;i<256;++i)
        f[i]=0;

    //le o ficheiro todo e conta a tabela de frequencia dos caracteres ASCII
    char c;
    unsigned char ch;
    while(infile.get(c))
    {
        ch=c;
        ++f[ch];
    }

    infile.clear();
    infile.seekg(0);

    Queue<Tree> q(3);
    Tree* tp;

    for(int i=0;i<256;++i)
    {
        //passa os char da tabela de frequencia para o output
        outfile.put(static_cast<unsigned char>(f[i]>>24));
        outfile.put(static_cast<unsigned char>((f[i]>>16)%256));
        outfile.put(static_cast<unsigned char>((f[i]>>8)%256));
        outfile.put(static_cast<unsigned char>(f[i]%256));

        if(f[i]>0)
        {
            tp=new Tree;
            (*tp).set_freq(f[i]);
            (*tp).set_char(static_cast<unsigned char>(i));
            q.enq(tp);
        }
    }

    //constroi a arvore principal
    Tree* tp2;
    Tree* tp3;

    do
    {
        tp=q.deq();
        if(!q.empty())
        {
            //pega nas arvores de menor frequencia e combina-as numa só
            tp2=q.deq();
            tp3=new Tree;
            (*tp3).set_freq((*tp).get_freq()+(*tp2).get_freq());
            (*tp3).set_left((*tp).get_root());
            (*tp3).set_right((*tp2).get_root());
            q.enq(tp3);
        }
    }
    while(!q.empty()); //ate as sub-arvores estarem todas numa só

    string H_table[256];
    unsigned char uc;
    for(unsigned short us=0;us<256;++us)
    {
        H_table[us]="";
        uc=static_cast<unsigned char>(us);
        (*tp).huf((*tp).get_root(), uc, "", H_table[us]);
    }

    if(verbose)
    {
        cout<<*tp<<endl;
        (*tp).huf_list((*tp).get_root(), "");
        cout<<"A tabela de frequencia é"<<sizeof(unsigned int)*256<<" bytes"<<endl;
    }

    unsigned int total_chars=(*tp).get_freq();

    unsigned char ch2;
    while(infile.get(c))
    {
        ch=c;
        //envia para o output a string bit a bit
        for(unsigned int i=0;i<H_table[ch].size();++i)
        {
            if(H_table[ch].at(i)=='0')
                ch2=0;
            if(H_table[ch].at(i)=='1')
                ch2=1;
            esc_huf(ch2, outfile);
        }
    }
    ch2=2;
    esc_huf(ch2, outfile);

    infile.close();
    outfile.close();

} //fim do compressor de Huffman

//Huffman Descompressor
void Huffman::descomprimir(string ifile, string ofile, bool verbose)
{
    ifstream infile(ifile.c_str(), ios::in|ios::binary);
    //abre o ficheiro de output
    ofstream outfile(ofile.c_str(), ios::out|ios::binary);
    if(!outfile)
    {
        cerr<<ofile<<"Não pode ser aberto"<<endl;
        exit(1);
    }

    //le a tabela de frequencias do ficheiro de input
    unsigned int f[256];
    char c;
    unsigned char ch;
    unsigned int j=1;
    for(int i=0;i<256;++i)
    {
        //le 4 bytes e combina-os num valor com 32 bits
        f[i]=0;
        for(int k=3;k>=0;--k)
        {
            infile.get(c);
            ch=c;
            f[i]+=ch*(j<<(8*k));
        }
    }

    //re-constroi a arvore de Huffman
    Queue<Tree> q(3);
    Tree* tp;

    for(int i=0;i<256;++i)
    {
        if(f[i]>0)
        {
            tp=new Tree;
            (*tp).set_freq(f[i]);
            (*tp).set_char(static_cast<unsigned char>(i));
            q.enq(tp);
        }
    }

    //constroi a arvore de Huffman principal
    Tree* tp2;
    Tree* tp3;

    do
    {
        tp=q.deq();
        if(!q.empty())
        {
            //pega nas duas arvores de Huffman com frequencia mais baixa e une-as
            tp2=q.deq();
            tp3=new Tree;
            (*tp3).set_freq((*tp).get_freq()+(*tp2).get_freq());
            (*tp3).set_left((*tp).get_root());
            (*tp3).set_right((*tp2).get_root());
            q.enq(tp3);
        }
    }
    while(!q.empty()); //ate todas as sub-arvores se unirem

    if(verbose)
    {
        cout<<*tp<<endl; //output da arvore de Huffman
        (*tp).huf_list((*tp).get_root(), "");
        cout<<"A tabela de frequecia e"<<sizeof(unsigned int)*256<<" bytes"<<endl;
    }

    //lê as strings do ficheiro de input
    string st;
    unsigned char ch2;
    unsigned int total_chars=(*tp).get_freq();
    while(total_chars>0) //continua ate nao haver mais nenhum char p/ descomprimir
    {
        st=""; //string de Huffman
        do
        {
            //lê as strings de Huffman bit a bit
            ch=le_huf(infile);
            if(ch==0)
                st=st+'0';
            if(ch==1)
                st=st+'1';
        } //procura a arvore de Huffman
        while(!(*tp).get_huf_char(st, ch2)); //continua ate encontrar um char

        outfile.put(static_cast<char>(ch2));
        --total_chars;
    }

    infile.close();
    outfile.close();

} //fim do descompressor
