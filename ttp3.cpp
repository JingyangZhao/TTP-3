#include <iostream>
#include <cstdio>
#include <vector>
#include <ctime>                                                 

#define total_number_normal_super_game 1 // the number of designs for super-games: normal/left/last
#define total_number_left_super_game 3 
#define total_number_last_super_game 62 

using namespace std;

int normal_super_game[total_number_normal_super_game+1][6+1][6+1]; // to store the designs of super-games
int left_super_game[total_number_left_super_game+1][6+1][6+1]; //
int last_super_game[total_number_last_super_game+1][6+1][10+1]; //

/****************************************************************************************************/
void lable(int i, vector<int> a, vector<int> &aa)/// find the best order from 3!*3!=36 cases
{
	int t1=a[1], t2=a[2], t3=a[3];	
	if(i==1) aa[1]=t1, aa[2]=t2, aa[3]=t3;
	else if(i==2) aa[1]=t1, aa[2]= t3, aa[3]=t2;	
	else if(i==3) aa[1]=t2, aa[2]= t1, aa[3]=t3;
	else if(i==4) aa[1]=t2, aa[2]= t3, aa[3]=t1;
	else if(i==5) aa[1]=t3, aa[2]= t1, aa[3]=t2;
	else if(i==6) aa[1]=t3, aa[2]= t2, aa[3]=t1;
}

/****************************************************************************************************/
int cost_normal(int t, vector<int> &aa, vector<int> &bb, vector<vector<int> > &D) // the cost of the t-th design of normal super-games
{
 	int res=0, days=6;
	int o[7]={0, aa[1],aa[2],aa[3], bb[1],bb[2],bb[3]};

	for(int i=1; i<=6; i++)
	{
		int flag=0;
		for(int d=1; d<=days; d++)
			if(d==days && normal_super_game[t][i][d]>0)
				if(flag==0) res += 2*D[ o[i] ][ o[normal_super_game[t][i][d]] ];	
				else res += D[ o[normal_super_game[t][i][d-1]] ][ o[normal_super_game[t][i][d]] ]+D[ o[normal_super_game[t][i][d]] ][ o[i] ];
			else if(normal_super_game[t][i][d]<0)
				if(flag==0) continue; 
				else res += D[ o[i] ][ o[normal_super_game[t][i][d-1]] ], flag=0;
			else
				if(flag==0) res += D[ o[i] ][ o[normal_super_game[t][i][d]] ], flag=1;
				else res += D[ o[normal_super_game[t][i][d-1]] ][ o[normal_super_game[t][i][d]] ];		
	} 
	return res;
}
int cost_left(int t, vector<int> &aa, vector<int> &bb, vector<vector<int> > &D) // the cost of the t-th design of left super-games
{
 	int res=0, days=6;
	int o[7]={0, aa[1],aa[2],aa[3], bb[1],bb[2],bb[3]};
	
	for(int i=1; i<=6; i++)
	{
		int flag=0;
		for(int d=1; d<=days; d++)
			if(d==days && left_super_game[t][i][d]>0)
				if(flag==0) res += 2*D[ o[i] ][ o[left_super_game[t][i][d]] ];	
				else res += D[ o[left_super_game[t][i][d-1]] ][ o[left_super_game[t][i][d]] ]+D[ o[left_super_game[t][i][d]] ][ o[i] ];
			else if(left_super_game[t][i][d]<0)
				if(flag==0) continue; 
				else res += D[ o[i] ][ o[left_super_game[t][i][d-1]] ], flag=0;
			else
				if(flag==0) res += D[ o[i] ][ o[left_super_game[t][i][d]] ], flag=1;
				else res += D[ o[left_super_game[t][i][d-1]] ][ o[left_super_game[t][i][d]] ];		
	} 
	return res;
}
int cost_last(int t, vector<int> &aa, vector<int> &bb, vector<vector<int> > &D)  // the cost of the t-th design of right super-games
{
 	int res=0;
	int o[7]={0, aa[1],aa[2],aa[3], bb[1],bb[2],bb[3]};
	
	for(int i=1; i<=6; i++)
	{
		int flag=0, days=10;
		for(int d=1; d<=days; d++)
			if(d==days && last_super_game[t][i][d]>0)
				if(flag==0) res += 2*D[ o[i] ][ o[last_super_game[t][i][d]] ];	
				else res += D[ o[last_super_game[t][i][d-1]] ][ o[last_super_game[t][i][d]] ]+D[ o[last_super_game[t][i][d]] ][ o[i] ];
			else if(last_super_game[t][i][d]<0)
				if(flag==0) continue; 
				else res += D[ o[i] ][ o[last_super_game[t][i][d-1]] ], flag=0;
			else
				if(flag==0) res += D[ o[i] ][ o[last_super_game[t][i][d]] ], flag=1;
				else res += D[ o[last_super_game[t][i][d-1]] ][ o[last_super_game[t][i][d]] ];		
	} 
	return res;
}
/****************************************************************************************************/
void type_M(vector<int> &a, vector<int> &b, int f, vector<vector<int> > &day, int d, vector<vector<int> > &D) // extending normal super-games
{ 
	if(f == -1) type_M(b, a, -f, day, d, D);
	else
	{
		vector<int> aa(4), bb(4); 
		int min=INT_MAX, t1,x1,y1;
		for(int t=1; t<=total_number_normal_super_game; t++)
		{
			for(int i=1; i<=6; i++)
			{
				for(int j=1; j<=6; j++)
				{			
					lable(i, a, aa); lable(j, b, bb);
					int temp = 0; cost_normal(t, aa, bb, D);
					if(temp<min) min=temp, t1=t, x1=i, y1=j;
				}
			}
		}
		// t1 th time table && oder x1+y1
		lable(x1, a, a), lable(y1, b, b);
		int o[7]={0, a[1],a[2],a[3], b[1],b[2],b[3]};
		 
		for(int i=1; i<=6; i++) 
			for(int j=1; j<=6; j++) 
				if(normal_super_game[t1][i][j]>0) day[ o[i] ][d+j-1] = o[normal_super_game[t1][i][j]];
				else day[ o[i] ][d+j-1] = - o[-normal_super_game[t1][i][j]];
				
		vector<int>().swap(aa), vector<int>().swap(bb);
	}
}
void type_L(vector<int> &a, vector<int> &b, int f, vector<vector<int> > &day, int d, vector<vector<int> > &D) // extending left super-games
{ 
	if(f == -1) type_L(b, a, -f, day, d, D);
	else
	{
		vector<int> aa(4), bb(4); 
		int min=INT_MAX, t1,x1,y1;
		for(int t=1; t<=total_number_left_super_game; t++)
		{
			for(int i=1; i<=6; i++)
			{
				for(int j=1; j<=6; j++)
				{			
					lable(i, a, aa); lable(j, b, bb);
					int temp = 0; cost_left(t, aa, bb, D);
					if(temp<min) min=temp, t1=t, x1=i, y1=j;
				}
			}
		}
		// t1 th time table && oder x1+y1
		lable(x1, a, a), lable(y1, b, b);
		int o[7]={0, a[1],a[2],a[3], b[1],b[2],b[3]};
		 
		for(int i=1; i<=6; i++) 
			for(int j=1; j<=6; j++) 
				if(left_super_game[t1][i][j]>0) day[ o[i] ][d+j-1] = o[left_super_game[t1][i][j]];
				else day[ o[i] ][d+j-1] = - o[-left_super_game[t1][i][j]];
				
		vector<int>().swap(aa), vector<int>().swap(bb);
	}
}

void type_Last(vector<int> &a, vector<int> &b, int f, vector<vector<int> > &day, int d, vector<vector<int> > &D) // extending last super-games
{ 
	if(f == -1) type_Last(b, a, -f, day, d, D);
	else
	{
		vector<int> aa(4), bb(4); 
		int min=INT_MAX, t1,x1,y1;
		for(int t=1; t<=total_number_last_super_game; t++)
		{
			for(int i=1; i<=6; i++)
			{
				for(int j=1; j<=6; j++)
				{			
					lable(i, a, aa); lable(j, b, bb);
					int temp = cost_last(t, aa, bb, D);
					if(temp<min) min=temp, t1=t, x1=i, y1=j;
				}
			}
		}
		// t1 th time table && oder x1+y1
		lable(x1, a, a), lable(y1, b, b);
		int o[7]={0, a[1],a[2],a[3], b[1],b[2],b[3]};
		 
		for(int i=1; i<=6; i++) 
			for(int j=1; j<=10; j++) 
				if(last_super_game[t1][i][j]>0) day[ o[i] ][d+j-1] = o[last_super_game[t1][i][j]];
				else day[ o[i] ][d+j-1] = -o[-last_super_game[t1][i][j]];
				
		vector<int>().swap(aa), vector<int>().swap(bb);
	}
}
/*****************************************************************************************/
int total_distance(int n, vector<vector<int> > &day,  vector<vector<int> > &D) // calculate the total distance of the schedule
{
	int res=0, days=2*n-2;
	for(int i=1; i<=n; i++)
	{
		int flag=0;
		for(int d=1; d<=days; d++)
			if(d==days && day[i][d]>0)
				if(flag==0) res += 2*D[i][day[i][d]];	
				else res += D[day[i][d-1]][day[i][d]]+D[day[i][d]][i];
			else if(day[i][d]<0)
				if(flag==0) continue; 
				else res += D[i][day[i][d-1]], flag=0;
			else
				if(flag==0) res += D[i][day[i][d]], flag=1;
				else res += D[day[i][d-1]][day[i][d]];		
	} 
	return res;
}
int ttp(int n, vector<vector<int> > &D, vector<vector<int> > &day, vector<vector<int> > &u) // ttp algorithm
{
	int m = n/3, f = 1;
	
	for(int i=1; i<=m-1; i++)
	{
		//u_0 = u_{m-2}
		int o = 1-i; if(o<=0) o = m-1+o;
			
		//Middle games between super-teams u_above, u_below; u_above is above u_below
		int ff = f, above, below;
		for(int j=1; j<=(m-2)/2; j++)
		{
			
			above = o+j, below = o-j; above += 2*(m-1), below +=  2*(m-1); above = above%(m-1), below = below%(m-1);
			if(above == 0) above= m-1; if(below == 0) below = m-1;
			
			if(i != m-1) type_M(u[above], u[below], ff, day, 6*i-5, D);
			else type_Last(u[above], u[below], ff, day, 6*i-5, D);
				
			//In the next slot, The direction of all arrows changes
			ff = -ff;
		}
		
		//Left games between super-teams u_l and u_o
		if(i==1 && m>2) type_M(u[o], u[m], -f, day, 6*i-5, D);
		else if(i != m-1) type_L(u[o], u[m], f, day, 6*i-5, D);
		else type_Last(u[o], u[m], f, day, 6*i-5, D);
		f = -f;
	}
	return total_distance(n, day, D);
}

int check(int n, int f_check, vector<vector<int> > &day) //check the correctness
{
	if(f_check){
	/************************************************************************************************************/
		//check for whether there is a missed game  
		vector<vector<int> > c(n+1, vector<int>(n+1));
		for(int i=1; i<=n; i++)	
			for(int j=1; j<=n; j++) 
				if(i!=j) c[i][j]=200;

		for(int i=1; i<=n; i++) 
			for(int j=1; j<=2*n-2; j++)
				if(day[i][j]>0) c[i][day[i][j]] += (-100+1);
				else c[i][-day[i][j]] += (-100-1);
		
		for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) if(c[i][j]!=0) {printf("missing games between teams: %d %d\n", i, j); return 1;}
	/************************************************************************************************************/
		//check for the condition of TTP-2: bounded-by-3
		for(int i=1; i<=n; i++)
			for(int d=1; d<=n*2-5; d++)
				if(day[i][d]>0 && day[i][d+1]>0 && day[i][d+2]>0 && day[i][d+3]>0) {printf("bounded-by-k: %d %d\n", i, d); return 1;}
				else if(day[i][d]<0 && day[i][d+1]<0 && day[i][d+2]<0 && day[i][d+3]<0) {printf("bounded-by-k: %d %d\n", i, d); return 1;}
	/************************************************************************************************************/
		//check for no-repeat
		for(int i=1; i<=n; i++) 
			for(int j=1; j<=2*n-2-1; j++) 
				if(day[i][j]==-day[i][j+1]) {printf("no-repeat between teams: %d %d\n", i, j); return 1;}
		
		for(int i=0; i<=n; i++) vector<int>().swap(c[i]); vector<vector<int> >().swap(c);
	}
	
	return 0;
}

void show_table(vector<vector<int> > &day, int n) //for showing the shcedule
{
	printf("\n/**************table****************/\n"); 
	for(int i=1; i<=n; i++,printf("\n")) for(int j=1; j<=2*n-2; j++) printf("%3d", day[i][j]);
}

void swap_triangle(int i, int j, int n, vector<vector<int> > &u) // swap triangles by swapping vertices i and j
{
	int ta=(i+2)/3,tb=(j+2)/3;
	int ia=i%3, ib=j%3; if(ia==0) ia=3; if(ib==0) ib=3;
	int m=u[ta][ia]; u[ta][ia]=u[tb][ib]; u[tb][ib]=m;
}


void swap_u(int i, int j, vector<vector<int> > &u) // swap super-teams u_i and u_j
{
	int t1=u[i][1], t2=u[i][2], t3=u[i][3];
	u[i][1]=u[j][1],u[i][2]=u[j][2],u[i][3]=u[j][3]; u[j][1]=t1,u[j][2]=t2,u[j][3]=t3;
}

void random_order(int n, vector<vector<int> > &u)
{
	int m=n/3;
	vector<int> list_number; 
	
	for(int i=1; i<=n; i++) list_number.push_back(i);
	
	random_shuffle(list_number.begin(), list_number.end());
	
	for(int i=1; i<=m; i++) for(int j=1; j<=3; j++) u[i][j]=list_number[3*(i-1)+j-1];
	
	vector<int>().swap(list_number);
}

int weight_triangle(int a, int b, int n, vector<vector<int> > D, vector<vector<int> > u) 
{
	int i=(a+2)/3, j=(b+2)/3;
	return D[u[i][1]][u[i][2]]+D[u[i][1]][u[i][3]]+D[u[i][2]][u[i][3]] + D[u[j][1]][u[j][2]]+D[u[j][1]][u[j][3]]+D[u[j][2]][u[j][3]];
}

void generate_triangle(int n, vector<vector<int> > D, vector<vector<int> > &u)
{
	vector<pair<int, int> > list;
	
	for(int i=1; i<=n; i++) for(int j=i+1; j<=n; j++) list.push_back(make_pair(i,j));
	
	int flag=1;
	while(flag)
	{
		random_shuffle(list.begin(), list.end());
		
		for(int i=0; i<list.size(); i++) 
		{
			int a=list[i].first, b=list[i].second;
			
			int before = weight_triangle(a, b, n, D, u);
			
			swap_triangle(a, b, n, u); //swap triangle team a and team b
			
			int after = weight_triangle(a, b, n, D, u);
			
			if(after < before) flag=2;
			else swap_triangle(a, b, n, u);
		} 
		flag--;
	}
	
	 
	vector<pair<int, int> >().swap(list);
} 
// swap super-teams----the local search part
void swap_super_team(int n, int &res, vector<vector<int> > &u, vector<vector<int> > &temp_day, vector<vector<int> > &day, vector<vector<int> > &D, int &f_improvement)
{
	int m=n/3;
	vector<pair<int, int> > list_m;
	for(int i=1; i<=m; i++) for(int j=i+1; j<=m; j++) list_m.push_back(make_pair(i,j));
	
	int flag=1;
	while(flag)
	{
		random_shuffle(list_m.begin(), list_m.end());
		
		for(int i=0; i<list_m.size(); i++) 
		{
			swap_u(list_m[i].first, list_m[i].second, u);
			
			int temp = ttp(n, D, temp_day, u);

			if(temp<res) 
			{
				res = temp, flag = 2; printf("%d ", res);
				for(int i=1; i<=n; i++) for(int j=1; j<=2*n-2; j++) day[i][j] = temp_day[i][j]; f_improvement=1;
			} 
			else swap_u(list_m[i].first, list_m[i].second, u);
		} 

		flag--;
	}
	vector<pair<int, int> >().swap(list_m);
}
/*
void swap_normal_team(int n, int &res, vector<vector<int> > &u, vector<vector<int> > &temp_day, vector<vector<int> > &day, vector<vector<int> > &D, int &f_improvement)
{
	printf("swap normal teams:\n");
	
	vector<pair<int, int> > list_n;
	for(int i=1; i<=n; i++) for(int j=i+1; j<=n; j++) list_n.push_back(make_pair(i,j));
	
	int flag=1;
	
	while(flag)
	{
		random_shuffle(list_n.begin(), list_n.end());
		
		for(int i=0; i<list_n.size(); i++) 
		{
			swap_triangle(list_n[i].first, list_n[i].second, n, u);
			
			int temp = ttp(n, D, temp_day, u);
			
			if(temp<res) 
			{
				res = temp, flag = 2; printf("%d, ", res); f_improvement=1;
				for(int i=1; i<=n; i++) for(int j=1; j<=2*n-2; j++) day[i][j]=temp_day[i][j]; 
			} 
			else swap_triangle(list_n[i].first, list_n[i].second, n, u);
			
		} 
		
		flag--;
	}
	
	printf("\n");
	vector<pair<int, int> >().swap(list_n);
}
*/

int get_schedule(vector<vector<int> > &u, vector<vector<int> > &D, int n, int &res, vector<vector<int> > &day, int f_opt)
{
	int f_improvement=0;
	int m=n/3;
	vector<vector<int> > temp_day(n+1, vector<int>(2*n-2+1));
	
	//local search by swapping super-teams
	if(f_opt) swap_super_team(n, res, u, temp_day, day, D, f_improvement);
	
	//local search by swapping normal teams
	//if(f_opt) swap_normal_team(n, res, u, temp_day, day, D, f_improvement);
	
	for(int i=0; i<=n; i++) vector<int>().swap(temp_day[i]); vector<vector<int> >().swap(temp_day);
	
	return f_improvement;
}

void read_super_games(FILE *fp)
{
	fp=fopen("normal_super_game.txt", "r");  if(!fp)exit(0);
	for(int t=1; t<=total_number_normal_super_game; t++) for(int i=1; i<=6; i++) for(int j=1; j<=6; j++) fscanf(fp, "%d",&normal_super_game[t][i][j]); fclose(fp);
	
	fp=fopen("left_super_game.txt", "r");  if(!fp)exit(0);
	for(int t=1; t<=total_number_left_super_game; t++) for(int i=1; i<=6; i++) for(int j=1; j<=6; j++) fscanf(fp, "%d",&left_super_game[t][i][j]); fclose(fp);
	
	fp=fopen("last_super_game.txt", "r");  if(!fp)exit(0);
	for(int t=1; t<=total_number_last_super_game; t++) for(int i=1; i<=6; i++) for(int j=1; j<=10; j++) fscanf(fp, "%d",&last_super_game[t][i][j]); fclose(fp);
}
/****************************************************************************************************/
int main()
{
	//srand((unsigned int)time(NULL));
	
	clock_t s_clock = clock(); 
	
	FILE *fp;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// read the design of normal, left, and last super-games
	read_super_games(fp);
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	int n = 24, f_opt = 1; //f_opt = 1, the heuristic part
	
	char *s = "Galaxy"; //Galaxy NFL NL Super
	char *buf = new char[strlen(s) + sizeof(n) + 1]; sprintf(buf, "%s%d.txt", s, n);
	
	fp=fopen(buf, "r"); // read the distance matrix
	
	vector<vector<int> > D(n+1,vector<int>(n+1)); // to store the n*n Distance matrix
	vector<vector<int> > u(n/3+1, vector<int>(4)); // to store m=n/3 super-teams
	vector<vector<int> > day(n+1, vector<int>(2*n-2+1)); //to store the 2*(2n-2) schedule

	if(!fp)exit(0); for(int i=1; i<=n; i++) for(int j=1; j<=n; j++) fscanf(fp,"%d",&D[i][j]); fclose(fp); // read the input matrix 
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// find a triangle packing using a local search procedure
	
	int triangle=INT_MAX; printf("Start finding a (heuristic) triangle packing:\n");
	
	int count=0; vector<vector<int> > uu(n/3+1, vector<int>(4)); // to store a temporary triangle packing
	while(count<99) // stop if there is no improvement after 9 consecutive iterations
	{
		int f_improvement=1;
		random_order(n, uu); generate_triangle(n, D, uu);  // randomly generate a triangle packing
		int temp=0; for(int i=1; i<=n/3; i++) temp += D[uu[i][1]][uu[i][2]]+D[uu[i][1]][uu[i][3]]+D[uu[i][2]][uu[i][3]];
		if(temp<triangle) 
		{
			printf("%d ", temp); triangle=temp;
			for(int i=1; i<=n/3; i++) u[i][1]=uu[i][1],u[i][2]=uu[i][2],u[i][3]=uu[i][3];
			count=0, f_improvement=0;
		}
		count += f_improvement;
	}
	
	int packing=0;
	for(int i=1; i<=n/3; i++) packing += D[u[i][1]][u[i][2]]+D[u[i][1]][u[i][3]]+D[u[i][2]][u[i][3]];
	
	printf("\nA good triangle packing has been found: %f seconds.\n", (double)(clock() - s_clock) / CLOCKS_PER_SEC);
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// TTP algorithm
	
	int res=ttp(n, D, day, u); count=0; printf("\nStart finding a (heuristic) TTP-3:\n%d ",res);
	while(f_opt && count<9) // stop if there is no improvement after 9 consecutive iterations
	{
		int f_improvement=get_schedule(u, D, n, res, day, f_opt);
		if(f_improvement==0) count++;
		else count=0;
	}
	
	show_table(day, n);
	
	printf("Final res: %d (Error: %d)\n", total_distance(n,day,D), check(n,1,day));
	
	cout << "The total run time is: " <<(double)(clock() - s_clock) / CLOCKS_PER_SEC << "s" << endl;
	
	for(int i=0; i<=n; i++) vector<int>().swap(D[i]), vector<int>().swap(day[i]); vector<vector<int> >().swap(D), vector<vector<int> >().swap(day);
	for(int i=0; i<=n/3; i++) vector<int>().swap(u[i]), vector<int>().swap(uu[i]); vector<vector<int> >().swap(u), vector<vector<int> >().swap(uu);
	return 0;
}
