#include <iostream>
#include <math.h>
#include <exception>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <ctime>
#include "Header.h"
#include <algorithm>


using namespace std;

double sqr(double x) { return x * x; }

void CalcNormals(Coord a, Coord b, Coord c, Coord& norm)
{
	double wrki;
	Coord v1, v2;

	v1.x = a.x - b.x;
	v1.y = a.y - b.y;
	v1.z = a.z - b.z;

	v2.x = b.x - c.x;
	v2.y = b.y - c.y;
	v2.z = b.z - c.z;

	wrki = sqrt(sqr(v1.y * v2.z - v1.z * v2.y) + sqr(v1.z * v2.x - v1.x * v2.z) + sqr(v1.x * v2.y - v1.y * v2.x));
	norm.x = (v1.y * v2.z - v1.z * v2.y) / wrki;
	norm.y = (v1.z * v2.x - v1.x * v2.z) / wrki;
	norm.z = (v1.x * v2.y - v1.y * v2.x) / wrki;
}

int main() {

	int n=0, el=0;
	std::vector<Coord> nodes;
	Coord norm;
	std::vector<std::vector<int>> elem;
	int h, m, tc, rc, aa, gt, exf, sz;

	std::vector<std::vector<int>> facet;
	facet.resize(6);

	facet[0].push_back(0); facet[0].push_back(1); facet[0].push_back(2); facet[0].push_back(3);
	facet[1].push_back(4); facet[1].push_back(5); facet[1].push_back(6); facet[1].push_back(7);
	facet[2].push_back(0); facet[2].push_back(1); facet[2].push_back(5); facet[2].push_back(4);
	facet[3].push_back(1); facet[3].push_back(2); facet[3].push_back(6); facet[3].push_back(5);
	facet[4].push_back(2); facet[4].push_back(3); facet[4].push_back(7); facet[4].push_back(6);
	facet[5].push_back(3); facet[5].push_back(0); facet[5].push_back(4); facet[5].push_back(7);

	std::vector<std::vector<int>> facet_ordered;
	facet_ordered.resize(6);

	facet_ordered[0].push_back(0); facet_ordered[0].push_back(1); facet_ordered[0].push_back(2); facet_ordered[0].push_back(3);
	facet_ordered[1].push_back(4); facet_ordered[1].push_back(5); facet_ordered[1].push_back(6); facet_ordered[1].push_back(7);
	facet_ordered[2].push_back(0); facet_ordered[2].push_back(1); facet_ordered[2].push_back(4); facet_ordered[2].push_back(5);
	facet_ordered[3].push_back(1); facet_ordered[3].push_back(2); facet_ordered[3].push_back(5); facet_ordered[3].push_back(6);
	facet_ordered[4].push_back(2); facet_ordered[4].push_back(3); facet_ordered[4].push_back(6); facet_ordered[4].push_back(7);
	facet_ordered[5].push_back(0); facet_ordered[5].push_back(3); facet_ordered[5].push_back(4); facet_ordered[5].push_back(7);

	std::vector<std::vector<int>> facetT;
	facetT.resize(4);

	facetT[0].push_back(0); facetT[0].push_back(1); facetT[0].push_back(3);
	facetT[1].push_back(1); facetT[1].push_back(2); facetT[1].push_back(3);
	facetT[2].push_back(2); facetT[2].push_back(0); facetT[2].push_back(3);
	facetT[3].push_back(0); facetT[3].push_back(2); facetT[3].push_back(1);

	std::vector<std::vector<int>> facet_orderedT;
	facet_orderedT.resize(4);

	facet_orderedT[0].push_back(0); facet_orderedT[0].push_back(1); facet_orderedT[0].push_back(3);
	facet_orderedT[1].push_back(1); facet_orderedT[1].push_back(2); facet_orderedT[1].push_back(3);
	facet_orderedT[2].push_back(0); facet_orderedT[2].push_back(2); facet_orderedT[2].push_back(3);
	facet_orderedT[3].push_back(0); facet_orderedT[3].push_back(1); facet_orderedT[3].push_back(2);

	
	string str1;
	string str2;
	string name;
	cout << "Enter the file name" << endl;
	cin >> name;
	int k = 0, te = 0, tn = 0;

	//ifstream fin("C:\\Users\\LENOVO\\Desktop\\Дипломная работа\\Сетки\\65201-3409050-75Static.k");
	ifstream fin(name);
	if ('t' == name[name.size() - 1]) {
		//Начало для txt-файлов
		if (fin.is_open()) {
			fin >> n;
			fin >> el;
			nodes.resize(n);
			elem.assign(el, vector<int>(8));

			for (int i = 0; i < n; i++) {
				fin >> nodes[i].x >> nodes[i].y >> nodes[i].z;
			}

			for (int i = 0; i < el; i++) {
				for (int j = 0; j < 8; j++) {
					fin >> elem[i][j];
				}
			}

			fin.close();
		}
		else
		{
			cout << "File is not found" << endl;
		}
		gt = 8;
		exf = 6;
		sz = 4;
			//Конец для txt-файлов
	}
	else {
		//Начало для k-файлов
		nodes.resize(1000000);
		elem.assign(1000000, vector<int>(8));
		if (fin.is_open()) {
			while (!fin.eof()) {
				fin >> str1;
				if ("*ELEMENT_SOLID" != str1) {
					fin.ignore(100, '\n');
				}
				else {
					fin.ignore(100, '\n');
					fin.ignore(100, '\n');
					fin >> str2;

					while ("*NODE" != str2) {
						if ("*NODE" == str2 || "*END" == str2) {
							break;
						}
						h = stoi(str2);
						fin >> m;
						te = h;
						for (int i = 0; i < 8; i++) {
							fin >> elem[h - 1][i];
						}
						fin >> str2;
					}
					fin.ignore(100, '\n');
					fin.ignore(100, '\n');

					fin >> str2;

					while ("*END" != str2) {
						if ("*END" == str2) {
							break;
						}
						h = stoi(str2);
						tn = h;
						fin >> nodes[h - 1].x;
						fin >> nodes[h - 1].y;
						fin >> nodes[h - 1].z;
						fin >> tc;
						fin >> rc;
						fin >> str2;
					}
				}




			}

			fin.close();
		}
		else
		{
			cout << "File is not found" << endl;
		}
		el = te;
		elem.resize(el);
		n = tn;
		nodes.resize(n);
		if (elem[0][3] == elem[0][4]) {
			for (int i = 0; i < el; i++) {
				elem[i].resize(4);
			}
			gt = 4;
			exf = 4;
			sz = 3;
		}
		else {
			gt = 8;
			exf = 6;
			sz = 4;
		}
		//Конец для k-файлов
	}
	
	

	std::vector<std::vector<int>> external_facets;
	external_facets.assign(el, vector<int>(exf));

	std::vector<std::vector<double>> N_E;
    N_E.resize(n);

	std::vector<std::vector<double>> facets;
	facets.resize(el);

	std::vector<std::vector<double>> facetsN;
	facetsN.resize(el);

	std::vector<std::vector<double>> facetsND;
	facetsND.resize(el);

	for (int i = 0; i < el; i++) {
		for (int j = 0; j < exf; j++) {
			external_facets[i][j]=j;
		}
	}

	for (int i = 0; i < el; i++) {
		for (int j = 0; j < gt; j++) {
			N_E[elem[i][j] - 1].push_back(i);
		}
	}

	std::vector<int> vect1;
	std::vector<int> vect2;

	if (size(elem[0]) == 8) {
		for (int i = 0; i < n; i++) {
			if (size(N_E[i]) != 1) {
				for (int j = 0; j < size(N_E[i]) - 1; j++) {
					for (int k = j + 1; k < size(N_E[i]); k++) {
						for (int l = 0; l < gt; l++) {
							for (int m = 0; m < gt; m++) {
								if (elem[N_E[i][j]][l] == elem[N_E[i][k]][m]) {
									vect1.push_back(l);
									vect2.push_back(m);
								}
							}
						}
						if (size(vect1) == sz) {
							sort(vect1.begin(), vect1.end());
							sort(vect2.begin(), vect2.end());

							for (int q = 0; q < exf; q++) {
								if (facet_ordered[q] == vect1) {
									for (int w = 0; w < size(external_facets[N_E[i][j]]); w++) {
										if (q == external_facets[N_E[i][j]][w]) {
											external_facets[N_E[i][j]].erase(external_facets[N_E[i][j]].begin() + w);
										}
									}
								}
								if (facet_ordered[q] == vect2) {
									for (int w = 0; w < size(external_facets[N_E[i][k]]); w++) {
										if (q == external_facets[N_E[i][k]][w]) {
											external_facets[N_E[i][k]].erase(external_facets[N_E[i][k]].begin() + w);
										}
									}
								}
							}

						}
						vect1.resize(0);
						vect2.resize(0);
					}
				}
			}
		}
	}

	if (size(elem[0]) == 4) {
		for (int i = 0; i < n; i++) {
			if (size(N_E[i]) != 1) {
				for (int j = 0; j < size(N_E[i]) - 1; j++) {
					for (int k = j + 1; k < size(N_E[i]); k++) {
						for (int l = 0; l < gt; l++) {
							for (int m = 0; m < gt; m++) {
								if (elem[N_E[i][j]][l] == elem[N_E[i][k]][m]) {
									vect1.push_back(l);
									vect2.push_back(m);
								}
							}
						}
						if (size(vect1) == sz) {
							sort(vect1.begin(), vect1.end());
							sort(vect2.begin(), vect2.end());
							for (int q = 0; q < exf; q++) {
								if (facet_orderedT[q] == vect1) {
									for (int w = 0; w < size(external_facets[N_E[i][j]]); w++) {
										if (q == external_facets[N_E[i][j]][w]) {
											external_facets[N_E[i][j]].erase(external_facets[N_E[i][j]].begin() + w);
										}
									}
								}
								if (facet_orderedT[q] == vect2) {
									for (int w = 0; w < size(external_facets[N_E[i][k]]); w++) {
										if (q == external_facets[N_E[i][k]][w]) {
											external_facets[N_E[i][k]].erase(external_facets[N_E[i][k]].begin() + w);
										}
									}
								}
							}

						}
						vect1.resize(0);
						vect2.resize(0);
					}
				}
			}
		}
	}


	std::vector<double> temp;
	temp.resize(4);
	int a, b, c;
	if (size(elem[0]) == 8) {
		for (int i = 0; i < el; i++) {

			for (int j = 0; j < size(external_facets[i]); j++) {
				temp[0] = elem[i][facet[external_facets[i][j]][0]] - 1;
				temp[1] = elem[i][facet[external_facets[i][j]][1]] - 1;
				temp[2] = elem[i][facet[external_facets[i][j]][2]] - 1;
				temp[3] = elem[i][facet[external_facets[i][j]][3]] - 1;

				a = temp[0]; b = temp[1]; c = temp[2];
				CalcNormals(nodes[a], nodes[b], nodes[c], norm);
				facetsN[i].push_back(norm.x); facetsN[i].push_back(norm.y); facetsN[i].push_back(norm.z);
				facets[i].push_back(a); facets[i].push_back(b); facets[i].push_back(c);


				a = temp[0]; b = temp[2]; c = temp[3];
				CalcNormals(nodes[a], nodes[b], nodes[c], norm);
				facetsN[i].push_back(norm.x); facetsN[i].push_back(norm.y); facetsN[i].push_back(norm.z);
				facets[i].push_back(a); facets[i].push_back(b); facets[i].push_back(c);
			}

		}
	}

	if (size(elem[0]) == 4) {
		for (int i = 0; i < el; i++) {

			for (int j = 0; j < size(external_facets[i]); j++) {
				temp[0] = elem[i][facetT[external_facets[i][j]][0]] - 1;
				temp[1] = elem[i][facetT[external_facets[i][j]][1]] - 1;
				temp[2] = elem[i][facetT[external_facets[i][j]][2]] - 1;

				a = temp[0]; b = temp[1]; c = temp[2];
				CalcNormals(nodes[a], nodes[b], nodes[c], norm);
				facetsN[i].push_back(norm.x); facetsN[i].push_back(norm.y); facetsN[i].push_back(norm.z);
				facets[i].push_back(a); facets[i].push_back(b); facets[i].push_back(c);


			}

		}
	}
	
	ofstream fout("figure.stl");
	fout << "solid Figure_Created_by_Laura3D" << endl;
	for (int i = 0; i < el; i++) {
		for (int j = 0; j < size(facets[i]) / 3; j++) {
			fout << "facet normal " << facetsN[i][3 * j] << " " << facetsN[i][3 * j + 1] << " " << facetsN[i][3 * j + 2] << endl;
			fout << "outer loop" << endl;
			fout << "vertex " << nodes[facets[i][3 * j]].x << " " << nodes[facets[i][3 * j]].y << " " << nodes[facets[i][3 * j]].z << endl;
			fout << "vertex " << nodes[facets[i][3 * j + 1]].x << " " << nodes[facets[i][3 * j + 1]].y << " " << nodes[facets[i][3 * j + 1]].z << endl;
			fout << "vertex " << nodes[facets[i][3 * j + 2]].x << " " << nodes[facets[i][3 * j + 2]].y << " " << nodes[facets[i][3 * j + 2]].z << endl;
			fout << "endloop" << endl;
			fout << "endfacet" << endl;
		}
	}

	fout << "endsolid Figure_Created_by_Laura3D" << endl;
	fout.close();

	cout << "1 - with displacement, 2 - without displacement" << endl;
	cin >> aa;
	if (aa == 1) {

		//Начало для перемещений
		std::vector<Coord> disp;
		disp.resize(n);

		ifstream fim("Все перемещения.txt");
		if (fim.is_open()) {
			fim.ignore(50, '\n');
			fim.ignore(50, '\n');
			for (int i = 0; i < n; i++) {
				fim >> disp[i].x >> disp[i].y >> disp[i].z;
			}
			fim.close();
		}
		else
		{
			cout << "File is not found" << endl;
		}

		for (int i = 0; i < n; i++) {
			disp[i].x += nodes[i].x;
			disp[i].y += nodes[i].y;
			disp[i].z += nodes[i].z;
		}

		for (int i = 0; i < el; i++) {
			for (int j = 0; j < size(facets[i])/3; j++) {
				a = facets[i][j * 3];
				b = facets[i][j * 3 + 1];
				c = facets[i][j * 3 + 2];

				CalcNormals(disp[a], disp[b], disp[c], norm);
				facetsND[i].push_back(norm.x); facetsND[i].push_back(norm.y); facetsND[i].push_back(norm.z);

			}
		}

		ofstream foutt("figuree.stl");
		foutt << "solid Figure_Created_by_Laura3D" << endl;
		for (int i = 0; i < el; i++) {
			for (int j = 0; j < size(facets[i]) / 3; j++) {
				foutt << "facet normal " << facetsND[i][3 * j] << " " << facetsND[i][3 * j + 1] << " " << facetsND[i][3 * j + 2] << endl;
				foutt << "outer loop" << endl;
				foutt << "vertex " << disp[facets[i][3 * j]].x << " " << disp[facets[i][3 * j]].y << " " << disp[facets[i][3 * j]].z << endl;
				foutt << "vertex " << disp[facets[i][3 * j + 1]].x << " " << disp[facets[i][3 * j + 1]].y << " " << disp[facets[i][3 * j + 1]].z << endl;
				foutt << "vertex " << disp[facets[i][3 * j + 2]].x << " " << disp[facets[i][3 * j + 2]].y << " " << disp[facets[i][3 * j + 2]].z << endl;
				foutt << "endloop" << endl;
				foutt << "endfacet" << endl;
			}
		}

		foutt << "endsolid Figure_Created_by_Laura3D" << endl;
		foutt.close();

		 //Конец для перемещений
	}
	unsigned int end_time = clock();
	cout << end_time << endl;

	system("pause");
	return 0;
}