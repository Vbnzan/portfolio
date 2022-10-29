#pragma once
#include <iostream>
#include <string>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <cmath>
#include <map>
#include<list>
using std::list;
using std::string;
using std::map;
using boost::numeric::ublas::matrix;
using boost::numeric::ublas::vector;

bool is_orthogonal(matrix<double> &matr, int size, double accurasy); //��������� ��������������� �������
void print_vect_4(vector<double> obj);
double angle_between_vectors(vector<double>& vec1, vector<double>& vec2);

class Moving;
class Affine_transformation;
class Projection;




class object {
public:
	virtual void print_self() =0;
	virtual object* transform_moving(typename Moving &a) = 0;
	virtual object* transform_Affine_transformation(Affine_transformation &a) = 0;
	virtual object* transform_projection(Projection&) = 0;
};

class simple_object : public object, public vector<double> { //����� ��� ������
public:
	virtual void print_self();
	simple_object() {};
	simple_object(vector<double> a);
	object* transform_moving(typename Moving& a);
	object* transform_Affine_transformation(Affine_transformation& a);
	object* transform_projection(Projection&);
};

class Line : public object { //������ � ������������ �������� ������ �� ��� � ������������
public:
	simple_object point;
	simple_object direction;
	void print_self();
	virtual object* transform_moving(typename Moving& a);
	object* transform_Affine_transformation(Affine_transformation& a);
	object* transform_projection(Projection&);
};





class Transformation { //�����-�� ��������������
private:
	string id;
protected:
	void set_id(string id) {
		this->id = id;
	}
public:
	virtual object* transform(object&) = 0;
	string get_id() const{
		return id;
	}
	virtual object* operator() (object& arg) 
	{ 
		printf("something is wrong\n");
		return &arg;
	}; //�� ������ �����������, ���������� ������� - ��������

	virtual simple_object* operator() (simple_object& arg) { return &arg; };
	virtual Line* operator() (Line& arg) { return &arg; };
};


class Moving : public Transformation{ //�������������� ��������
protected:
	matrix<double> turning_matrix;
	vector<double> moving_vect;
public:
	Moving();  //�������������� ��������������
	Moving(vector<double> &vect, string id); //����� �� ������
	Moving(vector<double> &direction, double rotation_angle, string id); //������� �� rotation_angle ������ ��� direction
	Moving(matrix<double> &turning_matrix, vector<double> &moving_vect, string id); //������� �������������� �� �������� ������� � ������� ���������	
	simple_object* operator() (simple_object &obj); //���������� ��������������
	Line* operator() (Line  &obj); //���������� ��������������
	void Print_self() const; //����� ���������� (����������, ��� ������� �����������)
	simple_object inverse_transformation(simple_object &obj); //���������� ��������� ��������������
	virtual object* transform(object& a) { return a.transform_moving(*this); }

};


class Affine_transformation : public Moving  //������� ������ ��������, ���������� �� ���� ������ ��������������
{
public:
	//Affine_transformation();
	Affine_transformation(int axis, double coeff, string id); //�������������� ���������� ����� axis �� coeff
	virtual object* transform(object& a) { return a.transform_Affine_transformation(*this); }
};


class Projection : public Transformation  //�������������� ��������
{
private:
	matrix<double> proj_matrix;
public:
	Projection(matrix<double> &projection_matrix, string id);
	simple_object* operator() (simple_object& obj); //���������� ��������������
	Line* operator() (Line& obj); //���������� ��������������
	virtual object* transform(object& a) { return a.transform_projection(*this); }
};

class Operation_list { //������ ��������������, �������� ����� ������� �� ����� ������� ��������� �����-������ �����
private:
	map<string, Transformation *> operations;
public:
	void add(Transformation *elem);
	void erase(string id);
	Transformation* find(string id); //����� ��������; ���������� NULL, ���� �������� ���� � ������
};

void print_list_of_objects(map<string, object*> list);


class  Programm_element { //������� ��������� �������������� - �������� ���� ��������
private:
	string trans;
	string argument;
	string result;
	Operation_list* operations; //������ ����� ��������������
	map<string, object*>* objects; //������ ����� �������
public:
	Programm_element(string trans, string argument, string result, Operation_list* operations, map<string, object*>* objects);
	int execute(); //��������� trans � argument, ���������� ��������� � result
};

class Programm_of_transformations {
private:
	list<Programm_element> programm; //������ ��������
 	Operation_list* operations; //������ ����� ��������������
	map<string, object*>* objects; //������ ����� �������
public:
	Programm_of_transformations(Operation_list* operations, map<string, object*>* objects);
	void add_elem(string trans, string argument, string result); 
	int execute(); //��������� ��������������� ��� ��������
};