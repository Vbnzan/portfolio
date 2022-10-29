#define PI 3.14159265      
#include "Moving.h"


void test_moving() {
	simple_object a; //������� �����
	a.resize(4);
	a(0) = 1;
	a(1) = 2;
	a(2) = 3;
	a(3) = 4;

	simple_object b; //������� ������
	b.resize(4);
	b.clear();
	b(0) = 1;

	vector<double> cc(4); //������� ��� ���� �����
	cc(0) = 2;
	cc(1) = 0;
	cc(2) = 1;
	cc(3) = 1;
	simple_object c(cc);

	//b.print_self();
	//c.print_self();



	Line line1; //c������ �����
	line1.direction = b;
	line1.point = c;

	vector<double> d(7); //������� ��������� ���

	a.print_self();

	Moving t0; //������� �������������� ��������������
	std::cout << "t0 - identity transformation" << std::endl;
	std::cout << "t0(a):" << std::endl;
	(*t0(a)).print_self(); //�������������� �������������� �� ������ �����

	Moving t1(b, "t1"); //����� �� ������ b
	std::cout << "t1 - shift by vector b = (1,0,0,0)" << std::endl;
	std::cout << "t1(a):" << std::endl;
	print_vect_4(*t1(a));  //����� �������� �����

	std::cout << "t1(b):" << std::endl; //����� �� �������� ������ 
	print_vect_4(*t1(b));

	std::cout << "line1" << std::endl;
	line1.print_self();
	std::cout << "t1(line1):" << std::endl; //����� �� ������ �����������, �� �������� �����
	Line* line2 = t1(line1);
	std::cout << "line direction" << std::endl;
	print_vect_4(line2->direction);
	std::cout << "line point" << std::endl;
	print_vect_4(line2->point);


	Moving t2(a, "t2"); //�������� ������� ����� �� ����� - ��������� ��������
	Moving wr(d, "wr"); //�������� ������� ����� �� ��������� ��� - ��������� ��������


	double angle1 = PI / 2;
	Moving t3(b, angle1, "t3"); //������� �� pi/2 ������ b
	std::cout << "t3 - rotation by the angle pi/2 along x-axis" << std::endl;
	std::cout << "t3(a):" << std::endl;
	print_vect_4(*t3(a));

	std::cout << "t3(line1):" << std::endl;
	Line* line3 = t3(line1);
	std::cout << "line direction" << std::endl;
	print_vect_4(line3->direction);
	std::cout << "line point" << std::endl;
	print_vect_4(line3->point);
	//��� ������ ��������������



	double angle2 = PI / 3;
	matrix<double> m1 = matrix<double>(3, 3);
	m1.clear();
	(m1)(0, 0) = cos(angle2);
	(m1)(0, 1) = -sin(angle2);
	(m1)(1, 1) = cos(angle2);
	(m1)(1, 0) = sin(angle2);
	(m1)(2, 2) = 1.; //������� ������������� �������
	std::cout << "is m1 orthogonal:  " << is_orthogonal(m1, 3, 0.0001) << std::endl;

	matrix<double> m2 = matrix<double>(3, 3);
	m2.clear();
	(m2)(0, 0) = 2;
	(m2)(0, 1) = -3;
	(m2)(1, 1) = 5;
	(m2)(1, 0) = sin(angle2); //������� �� ������������� �������
	std::cout << "is m2 orthogonal:  " << is_orthogonal(m2, 3, 0.0001) << std::endl;

	Moving t4(m1, b, "t4"); //������� �������������� � ������������� ��������
	std::cout << "t4(a):" << std::endl;
	print_vect_4(*t4(a));
	std::cout << "t4(line1):" << std::endl;
	Line* line4 = t4(line1);
	std::cout << "line direction" << std::endl;
	print_vect_4(line4->direction);
	std::cout << "line point" << std::endl;
	print_vect_4(line4->point);

	Moving t5(m2, b, "t5"); //���������� ������� �������������� � ������������� �������� - ��������� ��������
	Moving t6(m1, a, "t6"); //���������� ������� �������������� �� ������� �� ����� - ��������� ��������
	Moving t7(m1, d, "t7"); //���������� ������� �������������� �� ������� �� ��������� ��� - ��������� ��������

	std::cout << " inverse transformation of t4(a):" << std::endl; //�������� �������������� ���������� t4(a) ������� � a

	simple_object t4_a = *t4(a);
	print_vect_4(t4.inverse_transformation(t4_a));
	std::cout << "Hooray!" << std::endl;
	//t4.Print_self();




}


void test_transformation() {
	simple_object a; //������� �����
	a.resize(4);
	a(0) = 1;
	a(1) = 2;
	a(2) = 3;
	a(3) = 4;

	a.print_self();
	print_vect_4(a);

	simple_object b; //������� ������
	b.resize(4);
	b.clear();
	b(0) = 1;

	simple_object c; //������� ��� ���� �����
	c.resize(4);
	c(0) = 2;
	c(1) = 0;
	c(2) = 1;
	c(3) = 1;


	Line line1; //c������ �����
	line1.direction = b;
	line1.point = c;

	Affine_transformation af0(0, 10, "af0"); //������� ���������� �� ��� �
	std::cout << "af0(a)- stretching by 10 along x" << std::endl;
	std::cout << "af0(a):" << std::endl; //��� ������ �������������
	print_vect_4(*af0(a)); 
	std::cout << "af0(line1):" << std::endl;
	print_vect_4(af0(line1)->point);
	print_vect_4(af0(line1)->direction);

	Affine_transformation af1(5, 10, "af1"); //������� ���������� �� ��� "?", ��������� ��������

	matrix<double> m1 = matrix<double>(4, 4);
	m1.clear();
	m1(0, 1) = 1;
	m1(1, 3) = 1;
	m1(2, 0) = 1;
	m1(3, 2) = 1;

	Projection pr0(m1, "pr0"); //������� ��������
	std::cout << "pr0(a):" << std::endl;
	print_vect_4(*(pr0(a))); //��� ������ �������������
	std::cout << "pr0(line1):" << std::endl;
	print_vect_4(pr0(line1)->point);
	print_vect_4(pr0(line1)->direction);

	matrix<double> m2 = matrix<double>(3, 4); //������� ������������ �������
	Projection pr1(m2, "pr1"); //�������� ������� �������� - ��������� ��������

	
	Operation_list op; //������� ������� ��������������
	op.add(&pr0);
	op.add(&af0);
	op.erase("af0");  //�������� � �������, ���  ������

	map<string, object*> List_of_objects; //������� ������ ��������
	List_of_objects["a"] = &a;
	List_of_objects["line_1"] = &line1;

	//line1.print_self();
	print_list_of_objects(List_of_objects);
}


void test_programm_transformation()
{
	map<string, object*> List_of_objects; //������� ������ ��������

	simple_object a; //������� �����
	a.resize(4);
	a(0) = 1;
	a(1) = 2;
	a(2) = 3;
	a(3) = 4;

	simple_object b; //������� ������
	b.resize(4);
	b.clear();
	b(0) = 1;

	simple_object c; //������� ��� ���� �����
	c.resize(4);
	c(0) = 2;
	c(1) = 0;
	c(2) = 1;
	c(3) = 1;

	Line line1; //c������ �����
	line1.direction = b;
	line1.point = c;

	List_of_objects["a"] = &a; //�������� �������� � ������
	List_of_objects["b"] = &b;
	List_of_objects["c"] = &c;
	List_of_objects["line_1"] = &line1;


	Operation_list op; //������� ������� ��������������
	Affine_transformation af0(0, 10, "af0"); //������� ���������� �� ��� �

	matrix<double> m1 = matrix<double>(4, 4);
	m1.clear();
	m1(0, 1) = 1;
	m1(1, 3) = 1;
	m1(2, 0) = 1;
	m1(3, 2) = 1;

	Projection pr0(m1, "pr0"); //������� ��������

	double angle1 = PI / 2;
	Moving t3(b, angle1, "t3"); //������� ������� �� pi/2 ������ b

	op.add(&pr0); //�������� �������� � �������
	op.add(&af0);
	op.add(&t3);

	Programm_of_transformations pr(&op, &List_of_objects); //������� ���������
	//pr.add_elem("pr0", "a", "a"); //�������� �������� � ���������
	pr.add_elem("pr0", "a", "s");
	pr.add_elem("t3", "c", "a");
	pr.add_elem("af0", "line_1", "line_2");

	pr.execute(); //���������

	print_list_of_objects(List_of_objects);
}


int main() {
	//test_moving();
	//test_transformation();
	test_programm_transformation();
	return 0;
}