#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
//#include <sys/>



using namespace std;


void readByCin(auto& value) {
	while(1) {
		cin>>value;
		if(cin.fail()) {
			cout<<"input fail"<<endl;
			cout<<"please input again"<<endl;

			//clear cin
			cin.clear();
			cin.ignore(4096,'\n');

		}
		else {
			break;
		}

	}
}


class Student {
	public:
		string studentName;
		int studentID;
		bool sex;
		int birth;
		vector<int> scores;
		int sum=0;

		Student(string name,int ID) {
			//initial some values
			studentName = name;
			studentID = ID;
		}
		Student() {
		}
		~Student() {
			//cout<<"delete one item of  student information done"<<endl;
		}

		Student(const Student& stu) {
			studentID = stu.studentID;
			studentName = stu.studentName;
			sex = stu.sex;
			scores = stu.scores;
			birth = stu.birth;
			_getSumOfScores();
		}

		int _getSumOfScores() {
			for(int i=0; i<scores.size(); i++) {
				sum+=scores[i];
			}

		}


		void setValues(bool _sex,int _birth,vector<int> _scores) {
			if(_scores.size()==0) {
				cout<<"please input scores of the student"<<endl;
				return;
			}
			scores = _scores;
			sex = _sex;
			birth = _birth;
			//calculate sum
			_getSumOfScores();
		}

		//read value from input
		void readValues() {
			cout<<"please enter student information"<<endl;
			cout<<"student name: ";
			//			cin>>studentName;
			readByCin(studentName);
			cout<<"studentID: ";
			//			cin>>studentID;
			readByCin(studentID);
			cout<<"sex: (0 means for female and 1 means for male)";
			//			cin>>sex;
			readByCin(sex);
			cout<<"student birth: ";
			//			cin>>birth;
			readByCin(birth);
			cout<<"all scores: ";
			int score;
			for (int i=0; i<3; i++) {
				//				cin>>score;
				readByCin(score);
				scores.push_back(score);
			}
			_getSumOfScores();
			cout<<"finished"<<endl;

		}

		void setScores() {
			cout<<"please input three item of scores"<<endl;
			for(int i=0; i<3; i++) {
				readByCin(scores[i]);
			}
			//			cin>>scores[0]>>scores[1]>>scores[2];

		}
		//
		//		void readValues(){
		//
		//
		//		}


		void displayInformation() {
			cout<<"student "<<studentName<<"'s information"<<endl;
			cout<<"student name: "<<studentName<<endl;
			cout<<"student ID: "<<studentID<<endl;
			string s;
			if(sex) {
				s="male";
			}
			else {
				s = "female";
			}

			cout<<"student sex: "<<s<<endl;
			cout<<"student birth: "<<birth<<endl;
			cout<<"student scores: "<<endl;
			for(int i=0; i<scores.size(); i++) {
				cout<<scores[i]<<" ";
			}
			cout<<endl;
			cout<<"student global scores: "<<sum<<endl;
			cout<<endl;;

		}
};

class Node {
	public:
		Node(string name,int ID,bool sex,int birth,vector<int>&scores):stu(name,ID) {

			stu.setValues(sex,birth,scores);
			next = nullptr;
		}

		Node() {
			next = nullptr;
		}
		Node(const Student& _stu):stu(_stu) {
			next = nullptr;
		}
		~Node() {
			//cout<<"delete a node from linklist done"<<endl;
		}

		Student stu;

		Node* next;


};

class StudentLinkList {
	public:
		StudentLinkList() {

			initHeadAndLast();
		}

		~StudentLinkList() {
			Node* p = head;
			Node* q;
			while(p) {
				q=p->next;
				delete p;
				p = q;
			}
			//cout<<"delete Student link list done"<<endl;
		}

		void initHeadAndLast() {
			//last->stu is null and not use new
			last = new Node();
			last->next=nullptr;
			head=last;
		}

		StudentLinkList(string name,int ID,bool sex,int birth,vector<int>&scores) {
			initHeadAndLast();
			insertOne(name,ID,sex,birth,scores);
		}
		StudentLinkList(Student& stu) {
			initHeadAndLast();
			insertOne(stu);

		}


		void insertOne(string name,int ID,bool sex,int birth,vector<int>&scores) {
			Node* node = new Node(name,ID,sex,birth,scores);
			last->next = node;
			last = last->next;
			length++;
			//			cout<<"insert a student done"<<endl;
		}

		void insertOne(const Student& stu) {
			Node* node = new Node(stu);
			last->next = node;
			last = last->next;
			length++;
			//			cout<<"insert a student done"<<endl;
		}



		void deleteOne(string name) {
			Node* p = head;
			Node* q = p->next;
			while(q) {
				if(q->stu.studentName==name) {
					p->next=q->next;
					delete q;
					length--;
					return;
				}

				//find to the next one

				p=q;
				q=q->next;
			}

			return;

		}

		void deleteOne(int ID) {
			Node* p = head;
			Node* q = p->next;
			while(q) {
				if(q->stu.studentID==ID) {
					p->next=q->next;
					delete q;
					length--;
					return;
				}

				//find to the next one

				p=q;
				q=q->next;
			}
			cout<<"not exist "<<endl;
			return;

		}



		Node* findStudent(string name) {
			Node* p = head;
			Node* q = p->next;
			while(q) {
				if(q->stu.studentName==name) {
					return q;
				}

				//find to the next one

				p=q;
				q=q->next;
			}

			return nullptr;

		}

		Node* findStudent(int ID) {
			Node* p = head;
			Node* q = p->next;
			while(q) {
				if(q->stu.studentID==ID) {
					return q;
				}

				//find to the next one

				p=q;
				q=q->next;
			}

			return nullptr;

		}

		void findStudentAndDisplay(string name) {
			Node* node = findStudent(name);
			node->stu.displayInformation();
		}

		void findStudentAndDisplay(int ID) {
			Node* node = findStudent(ID);
			node->stu.displayInformation();
		}

		void findMaxAndMinScores() {
			//max must greater than -1
			if(length==0) {
				cout<<"list is too short"<<endl;
				return ;
			}
			int _mx=-100;
			int _mn=1000;
			Node* pmx;
			Node* pmn;
			Node* p = head;

			int cot=0;

			while(p->next) {
				p = p->next;
				if(p->stu.sum>_mx) {
					_mx = p->stu.sum;
					pmx = p;
				}
				if(p->stu.sum<_mn) {
					_mn = p->stu.sum;
					pmn = p;
				}

			}
			cout<<"student that owns max scores: "<<endl;
			pmx->stu.displayInformation();
			cout<<"student that owns min scores: "<<endl;
			pmn->stu.displayInformation();

			//store min and max
			max = pmx;
			min = pmn;
		}

		inline int getLength() {return length;}
		inline Node* getMin() {return min;}
		inline Node* getMax() {return max;}

	private:
		int length = 0;
		Node* min;
		Node* max;
		Node* head;
		Node* last;
};






namespace SIMS {
	StudentLinkList stulist ;


	void test() {
		//		vector<int> scores;
		//		scores.push_back(1);
		//		scores.push_back(2);
		//		scores.push_back(3);
		//		StudentLinkList stuList("breakpoint",10010,1,19960416,scores);
		//		stuList.findMaxAndMinScores();

		//		scores[0]=10,scores[1]=100,scores[2]=101;
		//		Student stu("diaoqiang",10011);
		//		stu.setValues(1,19961028,scores);
		//		stuList.insertOne(stu);
		//        stu.readValues();
		//		//		stuList.findMaxAndMinScores();
		//		int len = stuList.getLength();
		//		//		cout<<len<<endl;
		//		string name = "breakpoint";
		//		stuList.deleteOne(name);
		//		cout<<stuList.getLength()<<endl;
		//		stuList.findMaxAndMinScores();
		Student stu;
		stu.readValues();
		stulist.insertOne(stu);
		stulist.findMaxAndMinScores();
		//stulist.insertOne(stu);
		//stulist.findMaxAndMinScores();
	}


	void exit() {
		cout<<"system exit,goodbye"<<endl;
	}

	void menu() {

		cout<<"Welcome to SIMS"<<endl;
		while(true) {
			getchar();

			cout<<"1.find a student"<<endl;
			cout<<"2.insert a student"<<endl;
			cout<<"3.delete a student"<<endl;
			cout<<"4.find those students that own max and min scores"<<endl;
			cout<<"5.exit"<<endl;
			cout<<"please select a service"<<endl;
			int num;
			//			cin>>num;
			readByCin(num);
			//			cout<<"num: "<<num<<endl;
			switch(num) {
				case 1: {
						cout<<"please enter studentID or student name"<<endl;
						cout<<"1.studentID"<<endl;
						cout<<"2.student name"<<endl;
						int _num;
						//						cin>>_num;
						readByCin(_num);
						Node* node;
						//						cout<<"_num: "<<_num<<endl;
						switch(_num) {
							case 1:
								int studentID;
								cout<<"please enter studentID"<<endl;
								//								cin>>studentID;
								readByCin(studentID);
								node = stulist.findStudent(studentID);
								if(!node) {
									cout<<"student is not found"<<endl;
									break;
								}
								cout<<"the student that you find:"<<endl<<endl;
								node->stu.displayInformation();
								break;
							case 2: {
									string studentName;
									cout<<"please enter student name"<<endl;
									//									cin>>studentName;
									readByCin(studentName);
									node = stulist.findStudent(studentName);
									if(!node) {
										cout<<"student is not found"<<endl;
										break;
									}
									cout<<"the student that you find:"<<endl<<endl;
									node->stu.displayInformation();
									break;
								}

							default : {

									cout<<"please enter 1 or 2"<<endl;
									cout<<"back to main menu"<<endl;
								}

						}

						break;
					}

				case 2: {
						cout<<"please enter student information that you want yo insert"<<endl;
						Student stu;
						stu.readValues();
						stulist.insertOne(stu);
						break;
					}
				case 3: {

						cout<<"please enter studentID or student name"<<endl;
						cout<<"1.studentID"<<endl;
						cout<<"2.student name"<<endl;
						int _num;
						//						cin>>_num;
						readByCin(_num);
						switch(_num) {
							case 1:
								int studentID;
								cout<<"please enter studentID"<<endl;
								//								cin>>studentID;
								readByCin(studentID);
								stulist.deleteOne(studentID);
								break;
							case 2: {
									string studentName;
									cout<<"please enter student name"<<endl;
									//									cin>>studentName;
									readByCin(studentName);
									stulist.deleteOne(studentName);
									break;
								}

							default: {
									cout<<"please enter 1 or 2"<<endl;
									cout<<"back to main menu"<<endl;
								}

						}
						break;
					}

				case 4:
					stulist.findMaxAndMinScores();

					break;
				case 5: {
						exit();
						return;
					}
				default:
					cout<<"please enter 1 ~ 4"<<endl;
					cout<<"back to main menu"<<endl;


			}
			cout<<"press enter to continue"<<endl;
			getchar();
			system("clear");
		}




	}


};






int main() {
	//	freopen("in.txt","r",stdin);
	using namespace SIMS;
	//	test();
	menu();



	return 0;
}
