/*
* @author: Magdalena Fijalkowska
* Email: magdalena.m.fijalkowska@gmail.com
*/
#include <stdio.h>
#include <stdlib.h>

void swapArray( int **a, int **b ){
  int *tmp = *a;
  *a = *b;
  *b = tmp;
}

int rules(int cell, int aliveNeighbours){
  if ((cell == 1) && (aliveNeighbours < 2)) {
    return 0;
  }
  // Cell dies due to overpopulation
  else if ((cell == 1) && (aliveNeighbours > 3)) {
    return 0;
  }
  // A new cell is born
  else if ((cell== 0) && (aliveNeighbours == 3)) {
    return 1;
  }
  // Remains the same
  else {
    return cell;
  }
}

void countCorners(int*grid, int*nextGen, int nrows, int ncols){
  //[0,0]
  nextGen[0] = rules(grid[0], grid[1]+grid[ncols]+grid[ncols+1]);
  //[0,ncols-1]
  nextGen[ncols-1] = rules(grid[ncols-1], grid[ncols-2]+grid[ncols*2-1]+grid[ncols*2-2]);
  //[nrows-1, 0]
  nextGen[(nrows-1)*ncols] = rules(grid[(nrows-1)*ncols], grid[(nrows-2)*(ncols)]+grid[(nrows-2)*ncols+1]+grid[(nrows-1)*ncols+1]);
  //[nrows-1, ncols-1]
  int aliveNeighbours =  grid[(nrows-2)*(ncols)+ ncols-2]+grid[(nrows-2)*ncols+ncols-1]+grid[(nrows-1)*ncols+ncols-2];
  nextGen[(nrows-1)*ncols+ncols-1] = rules(grid[(nrows-1)*ncols+ncols-1], aliveNeighbours);
}

void countOnEdges(int *grid, int * nextGen, int nrows, int ncols){
  // up
  int aliveNeighbours =0;
  for( int col = 1; col <ncols-1; col++){
    aliveNeighbours =0;
    for(int i =0; i<=1; i++){
      for(int j= -1; j<=1; j++){
        aliveNeighbours += grid[(0+i)*ncols+(col+j)];
      }
    }
    aliveNeighbours -= grid[col];
    nextGen[col] = rules(grid[col], aliveNeighbours);
  }
  //down
  for( int col = 1; col <ncols-1; col++){
    aliveNeighbours =0;
    for(int i =-1; i<=0; i++){
      for(int j= -1; j<=1; j++){
        aliveNeighbours += grid[(nrows-1+i)*ncols+(col+j)];
      }
    }
    aliveNeighbours -= grid[(nrows-1)*ncols+col];
    nextGen[(nrows-1)*ncols+col] = rules(grid[(nrows-1)*ncols+col], aliveNeighbours);
  }
  //left
  for( int row = 1; row <nrows-1; row++){
    aliveNeighbours =0;
    for(int i =-1; i<=1; i++){
      for(int j= 0; j<=1; j++){
        aliveNeighbours += grid[(row+i)*ncols+j];
      }
    }
    aliveNeighbours -= grid[row*ncols];
    nextGen[row*ncols] = rules(grid[row*ncols], aliveNeighbours);
  }
  //right
  for( int row = 1; row <nrows-1; row++){
    aliveNeighbours =0;
    for(int i =-1; i<=1; i++){
      for(int j= -1; j<=0; j++){
        aliveNeighbours += grid[(row+i)*ncols+(ncols-1+j)];
      }
    }
    aliveNeighbours -= grid[row*ncols+ncols-1];
    nextGen[row*ncols+ncols-1] = rules(grid[row*ncols+ncols-1], aliveNeighbours);
  }

}

int countNeighboursInside(int *grid, int m, int l, int ncols){
  int aliveNeighbours = 0;
  //count neighbours inside the matrix
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      aliveNeighbours +=  grid[(l+i)*ncols +(m+j)];
    }
  }
  aliveNeighbours -= grid[l*ncols + m];
  return aliveNeighbours;
}

int *createNextGen(int *grid, int *nextGen, int nrows, int ncols){
  int neighbours = 0;
  //Inside of matrix
  for (int l = 1; l < nrows-1 ; l++) {
    for (int m = 1; m < ncols-1 ; m++) {
    // finding no Of Neighbours
    // that are alive
      neighbours = countNeighboursInside(grid, m, l, ncols);
      nextGen[l*ncols+m] = rules(grid[l*ncols+m], neighbours);
    }
  }
  //Edges
  countOnEdges(grid, nextGen, nrows, ncols);
  //Corners
  countCorners(grid,nextGen,nrows,ncols);
  return nextGen;
}

int main(void) {

  int nrows, ncols, steps;
  scanf ("%d %d %d\n", &nrows,&ncols,&steps);
  char* matrix = (char*) malloc(sizeof(char)*nrows*ncols);
  int* nextGen = (int*) malloc(sizeof(int)*(nrows)*(ncols));
  int* grid = (int*) malloc(sizeof(int)*(nrows)*(ncols));

// populate grids with 0s
  for(int i =0; i<nrows;i++){
    for(int j=0; j<ncols; j++){
      nextGen[i*ncols+j] = 0;
      grid[i*ncols+j] = 0;
    }
  }

//Input matrix
  for (int i=0;i<nrows;i++) {
    char c;
    for (int j=0;j<ncols;j++) {
      scanf("%c",&matrix[i*ncols+j]);
      if(matrix[i*ncols+j] == 88){
        grid[i*ncols+j] = 1;
      }
      else {
        grid[i*ncols+j] = 0;
      }
    }
    //catch new line
    scanf("%c", &c);
  }

  //Do n number of times - number of generations
  for (int i=0; i<steps;i++){
    int *ptr = createNextGen(grid, nextGen, nrows, ncols);
    *nextGen = *ptr;
    swapArray(&nextGen, &grid);
  }

  //convert back to  X and .
  for(int i = 0; i<nrows; i++){
    for(int j = 0; j< ncols; j++){
      if (grid[i*ncols+j] == 1 ){
        matrix[i*ncols+j] = 'X';
      }
      else{
        matrix[i*ncols+j] = '.';
      }
      printf("%c", matrix[i*ncols+j]);
    }
    printf("\n");
  }

  free(matrix);
  free(nextGen);
  free(grid);
  return 0;
}
