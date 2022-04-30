#include<iostream>
#include <fstream>
#include "sha256.h"
#include <string>
#include <random>
#include <algorithm>
//#include <boost/functional/hash.hpp>
using namespace std;
string random_string()
{
	std::string str("0123456789abcdefghijklmnopqrstuvwxyz0123456789abcdefghijklmnopqrstuvwxyz");

	std::random_device rd;
	std::mt19937 generator(rd());

	std::shuffle(str.begin(), str.end(), generator);

	return str.substr(0, 64); // assumes 32 < number of characters in str
}
int generateHashSHA256(string key)
{

	hash<string> string_hash;

	int val = string_hash(key);
	if (val < 0) 
	{
		val= -1 * val;
		return val;

	}
	else
		return val;
}

class product_info
{
public:
	string product_name;
	string origin_name;
	//string private_key;   // hash valuee for every step
	product_info() {
		product_name = "";
		origin_name = "";

	}

	//bool sold_out_status;
	product_info(string name, string on)
	{
		product_name = name;
		origin_name = on;
		//private_key = piv_key;
		

	}
	void operator = (const product_info& D) {
		product_name = D.product_name;
		origin_name = D.origin_name;
	}
};


class BlockChain
{

	class DNode
	{
	public:
		string data;
		product_info* obj;
		 int curr_hash;
		 int prev_hash;

		DNode* next;
		DNode* prev;
		DNode() {
			data = "";
			obj = nullptr;
			curr_hash = 00000;
			prev_hash = 000000;
			next = nullptr;
			prev = nullptr;


		}
	};
public:
	DNode* head;
	DNode* tail;
	int totalElements;


	 int public_key;
	BlockChain()
	{
		this->head = this->tail = nullptr;
		this->totalElements = 0;
		public_key = 0000000000000000000;
	}

	bool isEmpty()
	{
		return !this->head;
	}


	void insertAtTail(string data, product_info* obj_)
	{
		if (isEmpty())
		{
			DNode* newNode = new DNode;
			newNode->next = newNode->prev = nullptr;
			newNode->data = data;
			newNode->prev_hash = 00000000000;
			newNode->data = data;
			newNode->obj = obj_;
			string dumy_name= obj_->origin_name;
			string dumy_o = obj_->origin_name;
			string key_made=dumy_o.append(dumy_name);
			string dumy_d = data;
			key_made = dumy_d.append(key_made);
			newNode->curr_hash = generateHashSHA256(key_made);

			this->head = this->tail = newNode;

			this->totalElements++;
			
		}
		else
		{
			DNode* newNode = new DNode;
			newNode->data = data;
			newNode->prev_hash = tail->curr_hash;
			newNode->obj = obj_;
			string dumy_name = obj_->origin_name;
			string dumy_o = obj_->origin_name;
			string key_made = dumy_o.append(dumy_name);
			string dumy_d = data;
			key_made = dumy_d.append(key_made);
			newNode->curr_hash = generateHashSHA256(key_made);
			//cout << "===== " << newNode->curr_hash << " =====" << endl;

			newNode->next = nullptr;
			newNode->prev = this->tail;
			this->tail->next = newNode;
			this->tail = newNode;
			this->totalElements++;
		}
	}



	void print()
	{

		DNode* tmp = head;
		while (tmp)
		{
			cout << endl;
			cout << "prev " << tmp->prev_hash << "  " << endl;
			cout << "curr " << tmp->curr_hash << "  " << endl;
			cout << tmp->data << endl;
			tmp = tmp->next;
		}
	}
	string ProductKey(string product)
	{
		string encrypt = "";

		for (int i = 0; (i < 100) && (product[i] != '\0'); i++)
		{
			encrypt = encrypt + (product[i]);
		}
		return encrypt;
	}
	void ProductThroughSupplyChain(product_info product)
	{
		DNode* tmp = head;
		int StepNumber = 0;
		while (tmp)
		{
			tmp = tmp->next;
			StepNumber++;
		}
		if (StepNumber == 6)
		{
			ProductKey(product.product_name);
		}
	}
	void comparison(BlockChain arr[10], string name, int key,string comapny)
	{
		int i = 0;
		bool company_yes = true;

		while (i < 10)
		{
			
			DNode* curr = arr[i].head;
			if (curr != nullptr) 
			{
				if (name == curr->obj->product_name)
				{
					if (comapny == curr->obj->origin_name) {
						if (arr[i].public_key == key)
						{

							cout << "Product verified!!!" << endl;
							cout << "Fully manufactured Product!!!" << endl; // if the product is fully manufactured
							return;
						}
						else
						{
							DNode* tmp = arr[i].head;
							while (tmp)
							{
								if (tmp->curr_hash == key)
								{
									cout << "Orignal product!!!!!!!" << endl;  //if we verify product at any step while manufacturing
									cout << "Product is under manufacturing " << endl;
									return;
								}
								//cout << tmp->data << endl;
								tmp = tmp->next;
							}


						}
					}
					else {
						company_yes = false;
					}


				}
			}
			i++;
		}

		if (company_yes == false)
		{

			cout << "Product is fake,bcz origin was not same!!!!" << endl;
			
		}
		else
		cout << "Product is fake, QR did'nt match!!!!" << endl;

	}
};

int main()
{


	
	
	string products[] = { "prod1","prod2","prod3","prod4","prod5" };
	string SupplySteps[] = { "Raw Material","Manufacture","Distribution","Wholesaler","Retailer","Customer" };
	BlockChain products_[10];
	


	fstream my_file;
	my_file.open("Orignal_products.txt", ios::in);
	if (!my_file) {
		cout << "No such file";
	}
	else {
		//char ch[20];
		int j = 0;
		while (!my_file.eof()) {
			//my_file >> ch;
			
			int step = 0;
			//cout << "Enter product name you want to manufacture :";
			string nm;
			
			my_file >> nm;
			//cout << "Enter origin of the product :";
			string on;
			my_file >> on;
			//cout << "-------------" << nm << on << endl;
			cout << "Product " << j + 1 << ": "<<nm<<endl;
			product_info* obj__ = new product_info;
			obj__->origin_name = on;
			obj__->product_name = nm;
			string pub_keyy = "public key";
			string final_public_key = pub_keyy.append(nm);
			while (step < 6)
			{
				products_[j].insertAtTail(SupplySteps[step], obj__);
				if (step == 5)
				{
					products_[j].public_key = generateHashSHA256(final_public_key);
				}
				step++;

			}
			products_[j].print();
			cout << "PUBLIC KEY OF THE " << nm << " after manufacturing:" << products_[j].public_key << endl;
			j++;
			cout << "=============================================" << endl;


			if (my_file.eof())
				break;

			//cout << ch;
		}

	}
	//my_file.close();


	//----------------------------------- CHECK 1 ---------------------------------------------------
	cout << "------------ CASE 2---------------------" << endl;
	string p_name = "lifeboy";

    string o_name = "unilever";
	
	
	int QR= 551887723;

	products_[9].comparison(products_, p_name, QR, o_name);

	cout << "------------ CASE 2---------------------" << endl;
	//-------------------------------------Check 2 ----------------------------------------------------
	 p_name = "lifeboy";

	 o_name = "subway";  //wrong origin


	 QR = 551887723;

	products_[9].comparison(products_, p_name, QR, o_name);
	cout << "------------ CASE 3---------------------" << endl;
	//-------------------------------------Check 3 ----------------------------------------------------
	p_name = "lifeboy";

	o_name = "unilever";  //wrong origin


	QR = 55187723;

	products_[9].comparison(products_, p_name, QR, o_name);

	
	system("pause");
	return 0;
}