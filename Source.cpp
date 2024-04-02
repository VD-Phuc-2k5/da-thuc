#include <iostream>
#include <ctype.h>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <math.h>

struct Donthuc
{
    float he_so;
    int bac;
};
struct Node
{
    Donthuc donthuc;
    Node* next;
};
struct List
{
    Node *head, *tail;
};
void initialize(List &l);
//
void nhapDathuc(std::string &input);
void chuan_hoa_chuoi(std::string &input);
//
Donthuc tao_don_thuc(float he_so, int bac);
Node* tao_nut_dslk(Donthuc dt);
void tao_dslk(List &l , std::string input);
void them_nut(List &l, Node* node);
void in_da_thuc(List l);
void in_don_thuc(Donthuc p);
//
float quy_doi_ve_thap_phan(std::string he_so);
//
void swap(Donthuc &a, Donthuc &b);
void sx_da_thuc_bac_giam_dan(List l);
//
void xoa_phantu_sau_nut(List &l, Node* nut_hien_tai);
void xoa_don_thuc(List &l, int bac);
//
void rut_gon_dathuc(List &l);
//
void them_vao_cuoi_ds(List &l, Node* node);
void them_vao_dau_ds(List &l, Node* node);
void them_vao_sau_nut(List &l, Node* node, Node* current);
void them_mot_don_thuc(List &l, Donthuc p);
//
float tinh_gia_tri_da_thuc(List l, float x);
void cong_da_thuc(List dathuc1, List dathuc2); 
void tru_da_thuc(List dathuc1, List dathuc2);
void nhan_da_thuc(List dathuc1, List dathuc2);

int main()
{
    List dathuc1, dathuc2;
    std::string input;
    initialize(dathuc1);
	initialize(dathuc2);
	// tao da thuc 1
    nhapDathuc(input);
    chuan_hoa_chuoi(input);
    tao_dslk(dathuc1, input);
	// tao da thuc 2
	nhapDathuc(input);
    chuan_hoa_chuoi(input);
    tao_dslk(dathuc2, input);

	rut_gon_dathuc(dathuc1);
	//them_mot_don_thuc(dathuc1, tao_don_thuc(2, 3));
	in_da_thuc(dathuc1);
	in_da_thuc(dathuc2);
	std::cout << "Tong: " << std::endl;
	cong_da_thuc(dathuc1, dathuc2);
	std::cout << "Hieu: " << std::endl;
	tru_da_thuc(dathuc1, dathuc2);
	std::cout << "Nhan: " << std::endl;
	nhan_da_thuc(dathuc1, dathuc2);
	//std::cout << "gia tri cua da thuc khi x = 2: " << tinh_gia_tri_da_thuc(dathuc1, 2) << std::endl;
	system("pause");
	return 0;
}

void initialize(List &l)
{
    l.head = l.tail = NULL;
}
void nhapDathuc(std::string &input)
{
    std::cout << "Nhap da thuc: ";
    std::getline(std::cin, input);
}
void chuan_hoa_chuoi(std::string &input)
{
    std::stringstream ss(input);
    std::string res = "", word;
    while (ss >> word)
    {
        res += tolower(word[0]);
        for (int j = 1; j < word.size(); j++)
            res += tolower(word[j]);
        res += "";
    }
    res += word[word.size()];
    res.pop_back();
    input.assign(res);
}
Donthuc tao_don_thuc(float he_so, int bac)
{
    Donthuc donthuc;
    donthuc.he_so = he_so;
    donthuc.bac = bac;
    return donthuc;
}
Node* tao_nut_dslk(Donthuc dt)
{
    Node* node = new Node;
    if (node == NULL) return NULL;
    node->donthuc = dt;
    node->next = NULL;
    return node;
}
void tao_dslk(List &l , std::string input)
{
    int i = 0, vt = 0;
    Node* node = NULL;
    while (input[i] != '\0')
    {
        if (input[i] == 'x')
        {
            float he_so = quy_doi_ve_thap_phan(input.substr(vt, i - vt));
			int bac = input[i + 1] == '^' ? bac = std::stoi(input.substr(i+2, input.find('+', vt - i - 2))) : 1;
            node = tao_nut_dslk(tao_don_thuc(he_so, bac));
            them_nut(l, node);
            vt = input.find('+', vt) + 1;
        }
        ++i;
    }
}
void them_nut(List &l, Node* node)
{
    if(l.head == NULL)
        l.head = node;
    else
        l.tail->next = node;
    l.tail = node;
}
float quy_doi_ve_thap_phan(std::string he_so)
{
    if (he_so == "") return 1;
    std::istringstream iss(he_so);
    int numerator, denominator;
    char separator;
    iss >> numerator >> separator >> denominator;
    if (separator != '/')
        return std::stof(he_so);
    if (denominator == 0)
    {
        std::cout << "mau so cua phan so khong the bang 0\n";
		system("pause>0");;
        exit(0);
    }
    return static_cast<float>(numerator) / denominator;
}
void in_da_thuc(List l)
{
    while(l.head)
    {
        in_don_thuc(l.head->donthuc);
        std::cout << " + ";
        l.head = l.head->next;
    }
	std::cout << static_cast<char>(8) << " " << static_cast<char>(8);
    std::cout << static_cast<char>(8) << " " << static_cast<char>(8);
	std::cout << '\n';
}
void in_don_thuc(Donthuc p)
{
	if (p.he_so != 0)
		std::cout << p.he_so << "x^" << p.bac;
	else
		std::cout << '0';
}
//
void swap(Donthuc &a, Donthuc &b)
{
	Donthuc temp = a;
	a = b;
	b = temp;
}
void sx_da_thuc_bac_giam_dan(List l)
{
	if(l.head == NULL || l.head == l.tail) return;
	Node* p = l.head;
	while (p)
	{
		Node* max = p;
		for (Node* q = p->next; q != NULL; q=q->next)
			if (q->donthuc.bac > max->donthuc.bac)
				max = q;
		if (max != p)
			swap(max->donthuc, p->donthuc);
		p = p->next;
	}
}
//
void xoa_phantu_sau_nut(List &l, Node* current)
{
	if (l.head == NULL || current == NULL) return;
	if (current->next->next == NULL) l.tail = current;
	Node* next_next = current->next->next;
	delete current->next;
	current->next = next_next;
}
void xoa_don_thuc(List &l, int bac)
{
	if (l.head == NULL) return;
	rut_gon_dathuc(l);
	Node* current = l.head;
	while (current->next)
	{
		if (current->next->donthuc.bac == bac)
			break;
		current = current->next;
	}
	if (current->next != NULL)
		xoa_phantu_sau_nut(l, current);
	if (l.head->donthuc.bac == bac)
	{
		Node* temp = l.head;
		l.head = l.head->next;
		delete temp;
	}
}
//
void rut_gon_dathuc(List &l)
{
	if(l.head == NULL || l.head == l.tail) return;
	sx_da_thuc_bac_giam_dan(l);
	Node *next_next, 
		 *current = l.head;
	while (current->next)
	{
		if(current->next->donthuc.bac == current->donthuc.bac)
		{
			current->donthuc.he_so += current->next->donthuc.he_so;
			xoa_phantu_sau_nut(l, current);
		}
		else
			current = current->next;
	}
}
//
void them_vao_cuoi_ds(List &l, Node* node)
{
	l.tail->next = node;
	l.tail = node;
}
void them_vao_dau_ds(List &l, Node* node)
{
	node->next = l.head;
	l.head = node;
}
void them_vao_sau_nut(List &l, Node* node, Node* current)
{
	node->next = current->next;
	current->next = node;
}
void them_mot_don_thuc(List &l, Donthuc p)
{
	if (l.head == NULL) return;
	Node* node = tao_nut_dslk(p), 
		* current = l.head;
	while(current->donthuc.bac < p.bac && current->next != NULL)
		current = current->next;

	if (current->next == NULL)
	{
		if (current->donthuc.bac < p.bac)
			them_vao_dau_ds(l, node);
		else
			them_vao_cuoi_ds(l, node);
	}
	else
	{
		if (current->donthuc.bac < p.bac)
			them_vao_dau_ds(l, node);
		else
			them_vao_sau_nut(l, node, current);
	}
}
//
float tinh_gia_tri_da_thuc(List l, float x)
{
	float result = 0;
	while(l.head)
	{
		result += l.head->donthuc.he_so * pow(x, l.head->donthuc.bac);
		l.head = l.head->next;
	}
	return result;
}
void cong_da_thuc(List dathuc1, List dathuc2)
{
	List dathuc3;
	initialize(dathuc3);
	Node* node;
	while (dathuc1.head)
	{
		node = tao_nut_dslk(dathuc1.head->donthuc);
		them_nut(dathuc3, node);
		dathuc1.head = dathuc1.head->next;
	}
	while (dathuc2.head)
	{
		node = tao_nut_dslk(dathuc2.head->donthuc);
		them_nut(dathuc3, node);
		dathuc2.head = dathuc2.head->next;
	}
	rut_gon_dathuc(dathuc3);
	in_da_thuc(dathuc3);
}
void tru_da_thuc(List dathuc1, List dathuc2)
{
	List dathuc4;
	initialize(dathuc4);
	Node* node;
	int bac;
	float he_so;
	while (dathuc2.head)
	{
		bac = dathuc2.head->donthuc.bac;
		he_so = -1.0 * dathuc2.head->donthuc.he_so;
		node = tao_nut_dslk(tao_don_thuc(he_so, bac));
		them_nut(dathuc4, node);
		dathuc2.head = dathuc2.head->next;
	}
	while (dathuc1.head)
	{
		node = tao_nut_dslk(dathuc1.head->donthuc);
		them_nut(dathuc4, node);
		dathuc1.head = dathuc1.head->next;
	}
	rut_gon_dathuc(dathuc4);
	in_da_thuc(dathuc4);
}
void nhan_da_thuc(List dathuc1, List dathuc2)
{
	List dathuc5;
	initialize(dathuc5);
	Node* node;
	float he_so;
	int bac;
	for (Node *q = dathuc1.head; q != NULL; q = q->next)
	{
		for (Node* p = dathuc2.head; p != NULL; p = p->next)
		{
			he_so = q->donthuc.he_so * p->donthuc.he_so;
			bac = q->donthuc.bac + p->donthuc.bac;
			node = tao_nut_dslk(tao_don_thuc(he_so, bac));
			them_nut(dathuc5, node);
		}
	}
	rut_gon_dathuc(dathuc5);
	in_da_thuc(dathuc5);
}