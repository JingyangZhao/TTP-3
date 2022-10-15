This is an implement of one TTP algorithm in the paper:  
Jingyang Zhao, Mingyu Xiao, Chao Xu: Improved Approximation Algorithms for the Traveling Tournament Problem. MFCS 2022: 83:1-83:15  
https://drops.dagstuhl.de/opus/volltexte/2022/16881/pdf/LIPIcs-MFCS-2022-83.pdf  

We only implement the case:  TTP-3 with $n$ teams, where $n \bmod 6 = 0$. Note that for this case, there is a triangle packing of size $m=n/3$ and our construction is easier.

The code is written in c/c++ and the source file is a .cpp file.

Since $n \bmod 6 = 0$, there is a triangle packing of size $m=n/3$. Our schedule is based on a triangle packing.

Phase 1:  
The first step of algorithm is to generate a triangle packing with a small weight by using a heuristic method. In fact, our method usually can find the optimal packing on many instances.  
① Generate an arbitrary triangle packing;  
② We try to switch two vertices in the triangle packing to reduce the weight:  
     List $n(n-1)/2$ pairs $(i, j)$ in a random order, where $1\leq i &lt j \leq n$;  
     According to this order, check each pair $(i,j)$, whether we can reduce the weight by swapping teams $i$ and $j$, and we swap them if yes;  
③ After checking all pairs: if there is an improvement, we restart this local search in ②; if there is no improvement after 99 iterations of ②, return the final triangle packing.  

Phase 2:  
The second step of the algorithm is to construct a schedule according to the triangle packing.  
The main idea of the construction is as follows.  we take each triangle as a super-team and design super-games between super-teams. Then we extend super-games to normal games between normal teams.  
We have three kinds of super-games (SG): normal/left/last. In the paper, we describe one design for each of these super-games. Here we design more.  
One design for each normal SG; three different designs for each left SG; and 62 designs for each last SG. //These designs are obtained by using an ILP on 6 teams with some restrictions.   
The designs can be found in normal_super_game.txt, left_super_game.txt, and last_super_game.txt.  
In extending each SG between super-teams $u_i$ and $u_j$, there are three teams $\lbrace x_1, x_2, x_3\rbrace$ in $u_i$ and three teams $\lbrace y_1, y_2, y_3\rbrace$ in $u_j$.  
For each super-team, there are $3!=6$ ways to order the three teams. So, there are $3!\times 3!=36$ ways to order these six teams. We will use the best order.

Phase 3:  
Last we do the following local search to switch two super-teams to reduce the weight:   
① List $m(m-1)/2$ pairs $(u_i, u_j)$ of super-teams in a random order, where $1\leq i &lt j\leq m$ $(m=n/3)$;  
② According to this order, check each pair $(u_i,u_j)$, whether we can reduce the weight by swapping super-teams $u_i$ and $u_j$, and we swap them if yes (we will need to do Phase 2 after swapping a pair);  
③ After checking all pairs: if there is an improvement, we restart this local search in ②; if there is no improvement after 9 iterations of ②, return the final schedule.  


Some parameters in the code:  
int n: number of teams;  
int f_opt: a 0/1 variable indicating the last two heuristic parts;  
char *s: filname, e.g. Galaxy.

The information of the output scheudle:   
① It is a $n\times(2n-2)$ matrix;  
② The $i$-th row indicates team $t_i$, the $j$-th column indicates the $j$-th day in the schedule, item $t_{i,j}$ (resp., $-t_{i,j}$) on $i$-th row and $j$-th column indicates team $t_i$ play an away (resp., home) game with team $t_{i,j}$. 
