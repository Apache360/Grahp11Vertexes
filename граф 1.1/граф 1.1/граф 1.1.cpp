
#include "pch.h"
#include <iostream>
#include "windows.h" 
#include "stdio.h"
#include "math.h"
#include "ctime"

using namespace std;
const int size_of_arr_tops = 11;
int arr_tops[size_of_arr_tops] = { 1,2,3,4,5,6,7,8,9,10,11 };
const int row = 19;
const int col = 35;
int arr[row][col];
int arr_adjacency[size_of_arr_tops][size_of_arr_tops];
int arr_weight[size_of_arr_tops][size_of_arr_tops];
int starter_dijkstra;

void func_arr_set_swap_show()
{
	int cell_element;
	//задаю елементы главного массива
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			//задаю начало координат главного массива, что бы легче ориенироваться
			double x = (j - (col / 2));
			double y = (i - (row / 2));
			//задаю номера вершин графа в главный массив 
			if (y == 8 && x == -8)
			{
				cell_element = arr_tops[0];
			}
			else
			{
				if (y == 8 && x == 0)
				{
					cell_element = arr_tops[1];
				}
				else
				{
					if (y == 8 && x == 8)
					{
						cell_element = arr_tops[2];
					}
					else
					{
						if (y == 0 && x == -16)
						{
							cell_element = arr_tops[3];
						}
						else
						{
							if (y == 0 && x == -8)
							{
								cell_element = arr_tops[4];
							}
							else
							{
								if (y == 0 && x == 0)
								{
									cell_element = arr_tops[5];
								}
								else
								{
									if (y == 0 && x == 8)
									{
										cell_element = arr_tops[6];
									}
									else
									{
										if (y == 0 && x == 16)
										{
											cell_element = arr_tops[7];
										}
										else
										{
											if (y == -8 && x == -8)
											{
												cell_element = arr_tops[8];
											}
											else
											{
												if (y == -8 && x == 0)
												{
													cell_element = arr_tops[9];
												}
												else
												{
													if (y == -8 && x == 8)
													{
														cell_element = arr_tops[10];
													}
													else
													{
														//исключение рамок угловых верших графа (пустые, т.к. угловые вершины отсутствуют)
														if (((y == 7 || y == 8 || y == 9)
															|| (y == -7 || y == -8 || y == -9))
															&& ((x == 15 || x == 16 || x == 17)
																|| (x == -15 || x == -16 || x == -17)))
														{
															cell_element = 32;
														}

														else
														{
															//заполнение рамок остальных вершин графа (по сути задаем квадратами, но середина квадрата уже задана ранее, поэтому имеем только рамку)
															if (((y == 1 || y == 0 || y == -1)
																|| (y == 7 || y == 8 || y == 9)
																|| (y == -7 || y == -8 || y == -9))
																&& ((x == 1 || x == 0 || x == -1)
																	|| (x == 7 || x == 8 || x == 9)
																	|| (x == -7 || x == -8 || x == -9)
																	|| (x == 15 || x == 16 || x == 17)
																	|| (x == -15 || x == -16 || x == -17)))
															{
																cell_element = 64;
															}
															else
															{
																//задаю соединения между вершинами по матрице смежности
																int cell_connection_element = 42;
																//для вершины 1
																if ((arr_adjacency[0][1] != 0) && (y == 8) && (x == -2 || x == -3 || x == -4 || x == -5 || x == -6))
																{
																	cell_element = cell_connection_element;
																}
																else
																{
																	if ((arr_adjacency[0][3] != 0)
																		&& ((y == 6 && x == -10)
																			|| (y == 5 && x == -11)
																			|| (y == 4 && x == -12)
																			|| (y == 3 && x == -13)
																			|| (y == 2 && x == -14)))

																	{
																		cell_element = cell_connection_element;
																	}
																	else
																	{
																		if ((arr_adjacency[0][4] != 0)
																			&& (x == -8) && (y == 2 || y == 3 || y == 4 || y == 5 || y == 6))
																		{
																			cell_element = cell_connection_element;
																		}
																		else
																		{
																			if ((arr_adjacency[0][5] != 0)
																				&& ((y == 6 && x == -6)
																					|| (y == 5 && x == -5)
																					|| (y == 4 && x == -4)
																					|| (y == 3 && x == -3)
																					|| (y == 2 && x == -2)))
																			{
																				cell_element = cell_connection_element;
																			}
																			else
																			{
																				//для вершины 2
																				if ((arr_adjacency[1][2] != 0) && (y == 8) && (x == 2 || x == 3 || x == 4 || x == 5 || x == 6))
																				{
																					cell_element = cell_connection_element;
																				}
																				else
																				{
																					if ((arr_adjacency[1][4] != 0)
																						&& ((y == 6 && x == -2)
																							|| (y == 5 && x == -3)
																							|| (y == 4 && x == -4)
																							|| (y == 3 && x == -5)
																							|| (y == 2 && x == -6)))

																					{
																						cell_element = cell_connection_element;
																					}
																					else
																					{
																						if ((arr_adjacency[1][5] != 0)
																							&& (x == 0) && (y == 2 || y == 3 || y == 4 || y == 5 || y == 6))
																						{
																							cell_element = cell_connection_element;
																						}
																						else
																						{
																							if ((arr_adjacency[1][6] != 0)
																								&& ((y == 6 && x == 2)
																									|| (y == 5 && x == 3)
																									|| (y == 4 && x == 4)
																									|| (y == 3 && x == 5)
																									|| (y == 2 && x == 6)))
																							{
																								cell_element = cell_connection_element;
																							}
																							else
																							{
																								//для вершины 3
																								if ((arr_adjacency[2][5] != 0)
																									&& ((y == 6 && x == 6)
																										|| (y == 5 && x == 5)
																										|| (y == 4 && x == 4)
																										|| (y == 3 && x == 3)
																										|| (y == 2 && x == 2)))

																								{
																									cell_element = cell_connection_element;
																								}
																								else
																								{
																									if ((arr_adjacency[2][6] != 0)
																										&& (x == 8) && (y == 2 || y == 3 || y == 4 || y == 5 || y == 6))
																									{
																										cell_element = cell_connection_element;
																									}
																									else
																									{
																										if ((arr_adjacency[2][7] != 0)
																											&& ((y == 6 && x == 10)
																												|| (y == 5 && x == 11)
																												|| (y == 4 && x == 12)
																												|| (y == 3 && x == 13)
																												|| (y == 2 && x == 14)))
																										{
																											cell_element = cell_connection_element;
																										}
																										else
																										{
																											//вершина 4
																											if ((arr_adjacency[3][4] != 0) && (y == 0) && (x == -14 || x == -13 || x == -12 || x == -11 || x == -10))
																											{
																												cell_element = cell_connection_element;
																											}
																											else
																											{
																												if ((arr_adjacency[3][8] != 0)
																													&& ((y == -2 && x == -14)
																														|| (y == -3 && x == -13)
																														|| (y == -4 && x == -12)
																														|| (y == -5 && x == -11)
																														|| (y == -6 && x == -10)))
																												{
																													cell_element = cell_connection_element;
																												}
																												else
																												{
																													//вершина 5
																													if ((arr_adjacency[4][5] != 0)
																														&& (y == 0) && (x == -6 || x == -5 || x == -4 || x == -3 || x == -2))
																													{
																														cell_element = cell_connection_element;
																													}
																													else
																													{
																														if ((arr_adjacency[4][8] != 0)
																															&& (x == -8) && (y == -2 || y == -3 || y == -4 || y == -5 || y == -6))
																														{
																															cell_element = cell_connection_element;
																														}
																														else
																														{
																															if ((arr_adjacency[4][9] != 0)
																																&& ((y == -2 && x == -6)
																																	|| (y == -3 && x == -5)
																																	|| (y == -4 && x == -4)
																																	|| (y == -5 && x == -3)
																																	|| (y == -6 && x == -2)))
																															{
																																cell_element = cell_connection_element;
																															}
																															else
																															{

																																//вершина 6
																																if ((arr_adjacency[5][6] != 0)
																																	&& (y == 0) && (x == 2 || x == 3 || x == 4 || x == 5 || x == 6))
																																{
																																	cell_element = cell_connection_element;
																																}
																																else
																																{
																																	if ((arr_adjacency[5][8] != 0)
																																		&& ((y == -2 && x == -2)
																																			|| (y == -3 && x == -3)
																																			|| (y == -4 && x == -4)
																																			|| (y == -5 && x == -5)
																																			|| (y == -6 && x == -6)))
																																	{
																																		cell_element = cell_connection_element;
																																	}
																																	else
																																	{
																																		if ((arr_adjacency[5][9] != 0)
																																			&& (x == 0) && (y == -2 || y == -3 || y == -4 || y == -5 || y == -6))
																																		{
																																			cell_element = cell_connection_element;
																																		}
																																		else
																																		{
																																			if ((arr_adjacency[5][10] != 0)
																																				&& ((y == -2 && x == 2)
																																					|| (y == -3 && x == 3)
																																					|| (y == -4 && x == 4)
																																					|| (y == -5 && x == 5)
																																					|| (y == -6 && x == 6)))
																																			{
																																				cell_element = cell_connection_element;
																																			}
																																			else
																																			{
																																				//вершина 7
																																				if ((arr_adjacency[6][7] != 0)
																																					&& (y == 0) && (x == 10 || x == 11 || x == 12 || x == 13 || x == 14))

																																				{
																																					cell_element = cell_connection_element;
																																				}
																																				else
																																				{
																																					if ((arr_adjacency[6][9] != 0)
																																						&& ((y == -2 && x == 6)
																																							|| (y == -3 && x == 5)
																																							|| (y == -4 && x == 4)
																																							|| (y == -5 && x == 3)
																																							|| (y == -6 && x == 2)))

																																					{
																																						cell_element = cell_connection_element;
																																					}
																																					else
																																					{
																																						if
																																							((arr_adjacency[6][10] != 0)
																																								&& (x == 8) && (y == -2 || y == -3 || y == -4 || y == -5 || y == -6))
																																						{
																																							cell_element = cell_connection_element;
																																						}
																																						else
																																						{
																																							//вершина 8
																																							if ((arr_adjacency[7][10] != 0)
																																								&& ((y == -2 && x == 14)
																																									|| (y == -3 && x == 13)
																																									|| (y == -4 && x == 12)
																																									|| (y == -5 && x == 11)
																																									|| (y == -6 && x == 10)))
																																							{
																																								cell_element = cell_connection_element;
																																							}
																																							else
																																							{
																																								//вершина 9
																																								if ((arr_adjacency[8][9] != 0)
																																									&& (y == -8) && (x == -6 || x == -5 || x == -4 || x == -3 || x == -2))
																																								{
																																									cell_element = cell_connection_element;
																																								}
																																								else
																																								{
																																									//вершина 10
																																									if ((arr_adjacency[9][10] != 0)
																																										&& (y == -8) && (x == 2 || x == 3 || x == 4 || x == 5 || x == 6))
																																									{
																																										cell_element = cell_connection_element;
																																									}
																																									else
																																									{
																																										cell_element = 32;
																																									}
																																								}
																																							}
																																						}
																																					}
																																				}
																																			}
																																		}
																																	}
																																}
																															}
																														}
																													}
																												}
																											}
																										}
																									}
																								}
																							}
																						}
																					}
																				}
																			}
																		}
																	}
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			arr[i][j] = cell_element;
		}
	}
	//переварачиваю елементы главного массива (свап)
	for (int i = 0; i < row / 2; i++)
	{
		swap(arr[i], arr[row - i - 1]);
	}
	//вывожу елементы главного массива
	for (int i = 0; i < row; i++)
	{
		cout << endl;
		for (int j = 0; j < col; j++)
		{
			double x = (j - (col / 2));
			double y = (i - (row / 2));
			if (y == 8 && x == -8)
			{
				//вершина 9
				cout << arr[i][j] << " ";
			}
			else
			{
				if (y == 8 && x == 0)
				{
					//вершина 10
					cout << arr[i][j];
				}
				else
				{
					//11
					if (y == 8 && x == 8)
					{
						cout << arr[i][j];
					}
					else
					{
						if (y == 0 && x == -16)
						{
							cout << arr[i][j] << " ";
						}
						else
						{
							if (y == 0 && x == -8)
							{
								cout << arr[i][j] << " ";
							}
							else
							{
								if (y == 0 && x == 0)
								{
									cout << arr[i][j] << " ";
								}
								else
								{
									if (y == 0 && x == 8)
									{
										cout << arr[i][j] << " ";
									}
									else
									{
										if (y == 0 && x == 16)
										{
											cout << arr[i][j] << " ";
										}
										else
										{
											if (y == -8 && x == -8)
											{
												cout << arr[i][j] << " ";
											}
											else
											{
												if (y == -8 && x == 0)
												{
													cout << arr[i][j] << " ";
												}
												else
												{
													if (y == -8 && x == 8)
													{
														cout << arr[i][j] << " ";
													}
													else
													{
														if (true)
														{
															cout << (char)arr[i][j] << " ";
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	cout << endl<<endl<<endl;
}

void func_arr_adjacency_hand_filling(int i2, int j2, int i, int j)
{
	adjacency_hand_filling:
	cout << "Ребро вершин " << i2 << " и " << j2 << ": ";
	cin >> arr_adjacency[i][j];
	if (arr_adjacency[i][j] ==1|| arr_adjacency[i][j] == 0)
	{
		int temp_adjacency = arr_adjacency[i][j];
		arr_adjacency[j][i] = temp_adjacency;
		func_arr_set_swap_show();
	}
	else
	{
		cout << "Введите 0 или 1!"<<endl;
		goto adjacency_hand_filling;
	}
}

void func_arr_adjacency_rand_filling(int i, int j)
{
	arr_adjacency[i][j] = rand() % 2;
	int temp_adjacency = arr_adjacency[i][j];
	arr_adjacency[j][i] = temp_adjacency;
}

void algorithm_Dijkstra(int arr_weight[size_of_arr_tops][size_of_arr_tops], int st)
{
	int distance[size_of_arr_tops], count, index, i, u, m = st + 1;
	bool visited[size_of_arr_tops];
	for (i = 0; i < size_of_arr_tops; i++)
	{
		distance[i] = INT_MAX; visited[i] = false;
	}
	distance[st] = 0;

	//for (count = 0; count < size_of_arr_tops - 1; count++)
	//{
		int min = INT_MAX;
		for (i = 0; i < size_of_arr_tops; i++)
			if (!visited[i] && distance[i] <= min)
			{
				min = distance[i]; index = i;
			}
		u = index;
		visited[u] = true;
		for (i = 0; i < size_of_arr_tops; i++)
			if (!visited[i] && arr_weight[u][i] && distance[u] != INT_MAX &&
				distance[u] + arr_weight[u][i] < distance[i])
				distance[i] = distance[u] + arr_weight[u][i];
	//}
	cout << "Стоимость пути из начальной вершины до остальных:\t\n";
	for (i = 0; i < size_of_arr_tops; i++) 
	{
		if (distance[i] != INT_MAX)
			cout << m << " > " << i + 1 << " = " << distance[i] << endl;
		else cout << m << " > " << i + 1 << " = " << "маршрут недоступен" << endl;
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(NULL));

menu1:
	cout << "\n______________________________________________________________________\n";
	cout << "\n\t\tВИЗУАЛИЗАЦИЯ ГРАФА ПО МАТРИЦЕ СМЕЖНОСТИ\n\n";
	//обнуление матрицы смежности
	for (int i = 0; i < size_of_arr_tops; i++)
	{
		for (int j = 0; j < size_of_arr_tops; j++)
		{
			arr_adjacency[i][j] = 0;
		}
	}
	func_arr_set_swap_show();

	cout << "У данного графа доступно всего 22 ребра, ребра не пересекаются.\n"
		<< "В консоль необходимо писать только цифры!\n"
		<< "0 (в матрице смежности) - ребра нету.\n"
		<< "1 (в матрице смежности) - ребро есть.\n\n\n";
	

	//меню 1 (для матрицы смежности)
	cout << "Заполните матрицу смежности (11х11)" << endl <<
		"Нажмите 1, что бы заполнять вручную." << endl
		<< "Нажмите 2, что бы заполнить случайно." << endl
		<< "Нажмите 3, что бы выйти." << endl;
	char menu1_arr_adjacency_filling;
	cin >> menu1_arr_adjacency_filling;
	switch (menu1_arr_adjacency_filling)
	{
	case '1'://задаю елементы матрицы смежности вручную
		for (int i = 0; i < size_of_arr_tops; i++)
		{
			for (int j = 0; j < size_of_arr_tops; j++)
			{
				int i2 = i + 1;
				int j2 = j + 1;
				if (((i == 0) && (j == 1 || j == 3 || j == 4 || j == 5))
					|| ((i == 1) && (j == 2)))
				{
					func_arr_adjacency_hand_filling(i2, j2, i, j);
				}
				if ((arr_adjacency[0][5] == 0) && ((i == 1) && (j == 4)))
				{
					func_arr_adjacency_hand_filling(i2, j2, i, j);
				}
				if ((i == 1) && (j == 5 || j == 6))
				{
					func_arr_adjacency_hand_filling(i2, j2, i, j);
				}
				if ((arr_adjacency[1][6] == 0) && ((i == 2) && (j == 5)))
				{
					func_arr_adjacency_hand_filling(i2, j2, i, j);
				}
				if (((i == 2) && (j == 6 || j == 7))
					|| ((i == 3) && (j == 4 || j == 8))
					|| ((i == 4) && (j == 5 || j == 8 || j == 9))
					|| ((i == 5) && (j == 6)))
				{
					func_arr_adjacency_hand_filling(i2, j2, i, j);
				}
				if ((arr_adjacency[4][9] == 0) && ((i == 5) && (j == 8)))
				{
					func_arr_adjacency_hand_filling(i2, j2, i, j);
				}
				if (((i == 5) && (j == 9 || j == 10))
					|| ((i == 6) && (j == 7)))
				{
					func_arr_adjacency_hand_filling(i2, j2, i, j);
				}
				if ((arr_adjacency[5][10] == 0) && ((i == 6) && (j == 9)))
				{
					func_arr_adjacency_hand_filling(i2, j2, i, j);
				}
				if (((i == 6) && (j == 10))
					|| ((i == 7) && (j == 10))
					|| ((i == 8) && (j == 9))
					|| ((i == 9) && (j == 10)))
				{
					func_arr_adjacency_hand_filling(i2, j2, i, j);
				}
			}
		}
		break;
	case '2'://задаю елементы матрицы смежности случайно
		for (int i = 0; i < size_of_arr_tops; i++)
		{

			for (int j = 0; j < size_of_arr_tops; j++)
			{

				if (((i == 0) && (j == 1 || j == 3 || j == 4 || j == 5))
					|| ((i == 1) && (j == 2)))
				{
					func_arr_adjacency_rand_filling(i, j);
				}
				if ((arr_adjacency[0][5] == 0) && ((i == 1) && (j == 4)))
				{
					func_arr_adjacency_rand_filling(i, j);
				}
				if ((i == 1) && (j == 5 || j == 6))
				{
					func_arr_adjacency_rand_filling(i, j);
				}
				if ((arr_adjacency[1][6] == 0) && ((i == 2) && (j == 5)))
				{
					func_arr_adjacency_rand_filling(i, j);
				}
				if (((i == 2) && (j == 6 || j == 7))
					|| ((i == 3) && (j == 4 || j == 8))
					|| ((i == 4) && (j == 5 || j == 8 || j == 9))
					|| ((i == 5) && (j == 6)))
				{
					func_arr_adjacency_rand_filling(i, j);
				}
				if ((arr_adjacency[4][9] == 0) && ((i == 5) && (j == 8)))
				{
					func_arr_adjacency_rand_filling(i, j);
				}
				if (((i == 5) && (j == 9 || j == 10))
					|| ((i == 6) && (j == 7)))
				{
					func_arr_adjacency_rand_filling(i, j);
				}
				if ((arr_adjacency[5][10] == 0) && ((i == 6) && (j == 9)))
				{
					func_arr_adjacency_rand_filling(i, j);
				}
				if (((i == 6) && (j == 10))
					|| ((i == 7) && (j == 10))
					|| ((i == 8) && (j == 9))
					|| ((i == 9) && (j == 10)))
				{
					func_arr_adjacency_rand_filling(i, j);
				}
			}
		}
		break;
	case '3'://выйти из программы
		system("pause");
		return 0;
	default:
		cout << "Такой элемент меню отсутствует!" << endl<<endl;
		goto menu1;
	}

	//вывод матрицы смежности
	cout << endl << "Матрица смежности:" << endl;
	for (int i = 0; i < size_of_arr_tops; i++)
	{
		for (int j = 0; j < size_of_arr_tops; j++)
		{
			cout << arr_adjacency[i][j]<<"=Адрес:" << &arr_adjacency[i][j] << " ";
		}
		cout << endl<<endl;

	}
	cout <<endl;


	//меню 2 (для матрицы нагруженности)
menu2:
	func_arr_set_swap_show();
	cout << "Заполните матрицу нагруженности (11х11)" << endl <<
		"Нажмите 1, что бы заполнять вручную." << endl
		<< "Нажмите 2, что бы заполнить случайно." << endl
		<< "Нажмите 3, что бы пропустить заполнение." << endl
		<< "Нажмите 4, что бы вернуться в начало." << endl
		<< "Нажмите 5, что бы выйти." << endl;
	char menu2_arr_weight_filling;
	cin >> menu2_arr_weight_filling;
	switch (menu2_arr_weight_filling)
	{
	case '1'://задаю елементы матрицы нагруженности вручную
		for (int i = 0; i < size_of_arr_tops; i++)
		{
			for (int j = 0; j < size_of_arr_tops; j++)
			{
				int i2 = i + 1;
				int j2 = j + 1;

				if (arr_adjacency[i][j] != 0) 
				{
					weight_hand_filling:
					cout << "Ребро вершин " << i2 << " и " << j2 << ": ";
					cin >> arr_weight[i][j];
					if (arr_weight[i][j]==0)
					{
						cout << "Невозможно присвоить 0"<<endl;
						goto weight_hand_filling;
					}
				}
			}
		}
		break;
	case '2'://задаю елементы матрицы нагруженности случайно
		int range;
		cout << "Введите диапазон случайных чисел для матрицы нагруженности: ";
		cin >> range;
		
			for (int i = 0; i < size_of_arr_tops; i++)
		{
			for (int j = 0; j < size_of_arr_tops; j++)
			{
				if (arr_adjacency[i][j] != 0)
				{
				weight_rand_filling:
					arr_weight[i][j] = rand() % range;
					if (arr_weight[i][j] == 0)
					{
						goto weight_rand_filling;
					}
				}
			}
		}
		
		
		break;
	case '3'://пропустить заполнение матрицы нагруженности
		for (int i = 0; i < size_of_arr_tops; i++)
		{
			for (int j = 0; j < size_of_arr_tops; j++)
			{
				if (arr_adjacency[i][j] != 0)
				{
					arr_weight[i][j] = arr_adjacency[i][j];
				}
			}
		}
		break;
	case '4'://вернуться в начало
		goto menu1;
	case '5'://выйти из программы
		system("pause");
		return 0;
	default:
		cout << "Такой элемент меню отсутствует!" << endl << endl;
		goto menu2;
	}

	//вывод матрицы нагруженности
	cout << endl << "Матрица нагруженности:" << endl;
	for (int i = 0; i < size_of_arr_tops; i++)
	{
		for (int j = 0; j < size_of_arr_tops; j++)
		{
			cout << arr_weight[i][j] << "\t";
		}
		cout << endl<<endl;
	}
	cout << endl << endl;

	//меню 3 (для алгоритмов)
	menu3:
	cout << "Выберете пункт:" << endl <<
		"Нажмите 1, что бы найти кратчайшие маршруты от заданой вершины (алгоритм Дейкстри)." << endl
		<< "Нажмите 2, что бы вывести данный граф еще раз." << endl
		<< "Нажмите 3, что бы вернуться назад." << endl
		<< "Нажмите 4, что бы вернуться в начало." << endl
		<< "Нажмите 5, что бы выйти." << endl;
	char menu3_algorithm;
	cin >> menu3_algorithm;
	switch (menu3_algorithm)
	{
	case '1'://найти кратчайшие маршруты от заданой вершины
		cout << "Начальная вершина >> "; 
		cin >> starter_dijkstra;
		algorithm_Dijkstra(arr_weight, starter_dijkstra - 1);
		goto menu3;

	case '2'://вывести данный граф еще раз
		func_arr_set_swap_show();
		goto menu3;
	case '3'://вернуться назад
		goto menu2;
	case '4'://вернуться в начало
		goto menu1;
	case '5'://выйти из программы
		system("pause");
		return 0;
	default:
		cout << "Такой элемент меню отсутствует!" << endl << endl;
		goto menu3;
	}
	goto menu1;

	system("pause");
	return 0;
}
