#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static const double PI = 4.0 * atan2(1.0,1.0);

typedef struct
{
	int length;
	double * val;
	void setSize(int l){
		val = (double *)(malloc(l));
		int i;
		for(i=0; i<l; i++){
			val[i] = 0;
		}
		length = l;
	}
	void setPoint(int x, double v){
		val[x] = v;
	}
	double getPoint(int x){
		return val[x];
	}
	void remVector(){
		free(val);
	}
	void print(){
		printf("Vector -");
		int x;
		for(x=0; x<length; x++){
			printf("\n| %f |",val[x]);
		}
		printf("\n");
	}
	void scale(double s){
		int i;
		for(i=0; i<length; i++){
			val[i] *= s;
		}
	}
} Vector;
typedef struct
{
	double val[4];
} Vector4D;
typedef struct
{
	double val[3];
} Vector3D;
typedef struct
{
	double val[2];
} Vector2D;

typedef struct
{
	int cols;
	int rows;
	double * val;
	void setSize(int col, int row){
		val = (double *)(malloc(col*row));
		int x,y;
		for(x=0; x<row; x++){
			for(y=0; y<col; y++){
				val[x*col+y] = 0.0;
			}
		}
		cols = col;
		rows = row;
	}
	void setPoint(int col, int row, double v){
		val[row*cols+col] = v;
	}
	double getPoint(int col, int row){
		return val[row*cols+col];
	}
	void setRow(int y, Vector v){
		if(v.length==cols){
			int i;
			for(i=0; i<cols; i++){
				setPoint(i,y, v.getPoint(i));
			}
		}
	}
	void setCol(int x, Vector v){
		if(v.length==rows){
			int i;
			for(i=0; i<rows; i++){
				setPoint(x,i, v.getPoint(i));
			}
		}
	}
	Vector getRow(int y){
		Vector out;
		out.setSize(cols);
		int i;
		for(i=0; i<cols; i++){
			out.setPoint(i, getPoint(i,y));
		}
		return out;
	}
	Vector getCol(int x){
		Vector out;
		out.setSize(cols);
		int i;
		for(i=0; i<cols; i++){
			out.setPoint(i, getPoint(x,i));
		}
		return out;
	}
	double cofactor(int col, int row){
		if(col+row % 2 == 0){
			return 1;
		}
		else{
			return -1;
		}
	}
	void rowAdd(int row, Vector vect){
		if(vect.length==cols){
			int i;
			for(i=0; i<cols; i++){
				setPoint(i,row,getPoint(i,row)+vect.getPoint(i));
			}
		}
	}
	void rowSub(int row, Vector vect){
		if(vect.length==cols){
			int i;
			for(i=0; i<cols; i++){
				setPoint(i,row,getPoint(i,row)-vect.getPoint(i));
			}
		}
	}
	void rowMult(int row, double s){
		int i;
		for(i=0; i<cols; i++){
			setPoint(i,row,getPoint(i,row)*s);
		}
	}
	void rowDiv(int row, double s){
		int i;
		for(i=0; i<cols; i++){
			setPoint(i,row,getPoint(i,row)/s);
		}
	}
	void rowSwap(int row1, int row2){
		Vector temp = getRow(row1);
		setRow(row1,getRow(row2));
		setRow(row2,temp);
	}

	void remMatrix(){
		free(val);
	}
	void print(){
		printf("Matrix -");
		int x,y;
		for(x=0; x<rows; x++){

			if(x != 0 || x!= 3){
				printf("\n|");
				for(y=0; y<cols; y++){
					printf(" %f,",val[x*cols+y]);
				}
				printf(" |");
			}
			else{
				printf("\n-");
				for(y=0; y<cols; y++){
					printf(" %f,",val[x*cols+y]);
				}
				printf(" -");
			}
		}
		printf("\n");
	}
	void scale(double s){
		int i;
		for(i=0; i<cols*rows; i++){
			val[i] *= s;
		}
	}
} Matrix;
typedef struct
{
	Vector4D vect[4];
} Matrix4D;
typedef struct
{
	Vector3D vect[3];
} Matrix3D;
typedef struct
{
	Vector2D vect[2];
} Matrix2D;

//General functions
double toDeg(double rad);
double toRad(double deg);

//Vector functions
void zeroVector(Vector *v);
void setVector(double x, Vector *v);
bool equals(Vector v1, Vector v2);

//Vector4D functions
void zeroVector(Vector4D *v);
void scaleVector(double s, Vector4D *v);
void setVector(double a, double b, double c, double d, Vector4D *v);
void setVector(double x, Vector4D *v);
bool equals(Vector4D v1, Vector4D v2);
void toString(Vector4D v);

//Vector3D functions
void zeroVector(Vector3D *v);
void scaleVector(double s, Vector3D *v);
void setVector(double a, double b, Vector3D *v);
void setVector(double x, Vector3D *v);
bool equals(Vector3D v1, Vector3D v2);
void toString(Vector3D v);

//Vector2D functions
void zeroVector(Vector2D *v);
void scaleVector(double s, Vector2D *v);
void setVector(double a, double b, Vector2D *v);
void setVector(double x, Vector2D *v);
bool equals(Vector2D v1, Vector2D v2);
void toString(Vector2D v);

//Matrix functions
void zeroMatrix(Matrix * m);
void setMatrix(double z, Matrix * m);
bool equals(Matrix m1, Matrix m2);
Matrix4D to4DMatrix(Matrix m);
Matrix3D to3DMatrix(Matrix m);
Matrix2D to2DMatrix(Matrix m);

void REF(Matrix * m);

//Matrix4D functions
void zeroMatrix(Matrix4D *v);
void scaleMatrix(double s, Matrix4D *v);
void setMatrix(Vector4D a, Vector4D b, Vector4D c, Vector4D d, Matrix4D *v);
void setMatrix(double z, Matrix4D *v);
void setMatrix(double a1,double b1,double c1,double d1,
			   double a2,double b2,double c2,double d2,
			   double a3,double b3,double c3,double d3,
			   double a4,double b4,double c4,double d4, Matrix4D *m);
bool equals(Matrix4D m1, Matrix4D m2);
void toString(Matrix4D v);
double det(Matrix4D m);
void rowOPAdd(int row, Matrix4D * m, Vector4D vect);
void rowOPSub(int row, Matrix4D * m, Vector4D vect);
void rowOPMult(int row, Matrix4D * m, double s);
void rowOPDiv(int row, Matrix4D * m, double s);
void rowOPSwap(int row1, int row2, Matrix4D * m);
Vector4D getRow(int row, Matrix4D m);
Matrix toMatrix(Matrix4D m);

Vector4D add(Vector4D v1, Vector4D v2);
Vector4D linearTransformation(Vector4D input, Matrix4D basisTrans);
void transpose(Matrix4D * m);
void rotateVector(Vector4D * v, double degXY, double degYZ, double degXZ);
Matrix4D multiply(Matrix4D m1, Matrix4D m2);
void REF(Matrix4D * m);
int rank(Matrix4D m);
int dotProduct(Vector4D v1, Vector4D v2);

//Matrix3D functions
void zeroMatrix(Matrix3D *v);
void scaleMatrix(double s, Matrix3D *v);
void setMatrix(Vector3D a, Vector3D b, Vector3D c, Matrix3D *v);
void setMatrix(double z, Matrix3D *v);
void setMatrix(double a1,double b1,double c1,
			   double a2,double b2,double c2,
			   double a3,double b3,double c3, Matrix3D *m);
bool equals(Matrix3D m1, Matrix3D m2);
void toString(Matrix3D v);
Matrix3D subMatrix(int col, int row, Matrix4D in);
double det(Matrix3D m);
void rowOPAdd(int row, Matrix3D * m, Vector3D vect);
void rowOPSub(int row, Matrix3D * m, Vector3D vect);
void rowOPMult(int row, Matrix3D * m, double s);
void rowOPDiv(int row, Matrix3D * m, double s);
void rowOPSwap(int row1, int row2, Matrix3D * m);
Vector3D getRow(int row, Matrix3D m);
Matrix toMatrix(Matrix3D m);

Vector3D add(Vector3D v1, Vector3D v2);
Vector3D linearTransformation(Vector3D input, Matrix3D basisTrans);
void transpose(Matrix3D * m);
void rotateVector(Vector3D * v, double degXY, double degYZ, double degXZ);
Matrix3D multiply(Matrix3D m1, Matrix3D m2);
void REF(Matrix3D * m);
int rank(Matrix3D m);
int dotProduct(Vector3D v1, Vector3D v2);
Vector3D crossProduct(Vector3D v1, Vector3D v2);

//Matrix2D
void zeroMatrix(Matrix2D *v);
void scaleMatrix(double s, Matrix2D *v);
void setMatrix(Vector2D a, Vector2D b, Matrix2D *v);
void setMatrix(double z, Matrix2D *v);
void setMatrix(double a1,double b1,
			   double a2,double b2, Matrix2D *m);
bool equals(Matrix2D m1, Matrix2D m2);
void toString(Matrix2D v);
Matrix2D subMatrix(int col, int row, Matrix3D in);
double det(Matrix2D m);
void rowOPAdd(int row, Matrix2D * m, Vector2D vect);
void rowOPSub(int row, Matrix2D * m, Vector2D vect);
void rowOPMult(int row, Matrix2D * m, double s);
void rowOPDiv(int row, Matrix2D * m, double s);
void rowOPSwap(int row1, int row2, Matrix2D * m);
Vector2D getRow(int row, Matrix2D m);
Matrix toMatrix(Matrix2D m);

Vector2D add(Vector2D v1, Vector2D v2);
Vector2D linearTransformation(Vector2D input, Matrix2D basisTrans);
void transpose(Matrix2D * m);
void rotateVector(Vector2D * v, double degXY);
Matrix2D multiply(Matrix2D m1, Matrix2D m2);
void REF(Matrix2D * m);
int rank(Matrix2D m);
int dotProduct(Vector2D v1, Vector2D v2);
int crossProduct(Vector2D v1, Vector2D v2);

int main(int argc, char *args[]){
	
	/*Matrix2D mat1;
	Matrix2D mat2;
	Vector2D vect;

	zeroMatrix(&mat1);
	zeroMatrix(&mat2);
	zeroVector(&vect);

	setMatrix(1,1,
			  0,1,&mat1);
	toString(mat1);
	setMatrix(0,-1,
			  1,0,&mat2);
	toString(mat2);

	toString(multiply(mat1,mat2));
	//setVector(1,1,&vect);

	//printf("%f, %f\n",pi,cos(pi));
	//toString(mat);
	//transpose(&mat);
	//toString(mat);
	//toString(vect);
	//rotateVector(&vect,PI/2);
	//toString(vect);

	
	//toString(linearTransformation(vect,mat));
	*//*
	Matrix4D mat;
	Vector4D v;

	setVector(1,&v);
	//Vector4D vect4d;

	zeroMatrix(&mat);
	//zeroVector(&vect4d);

	setMatrix(0,0,0,0,
			  0,4,2,14,
			  0,2,1,7,
			  0,6,3,21, &mat);
	toString(mat);
	//toString(getRow(3,mat));
	toString(mat);
	printf("%d\n",rank(mat));
	//toString(mat);
	//toString(subMatrix(1,1,mat));
	//toString(vect4d);
	*/
	Matrix m;
	m.setSize(4,4);
	setMatrix(1.,&m);
	m.setPoint(2,0, 5.0);
	m.setPoint(1,1, 5.0);
	m.setPoint(3,1, 5.0);
	m.remMatrix();
	m.setPoint(3,1, 5.0);
	//m.scale(3.);
	//m.rowSwap(0,1);
	Vector v;
	v.setSize(4);
	v.print();
	//setVector(15,&v);

	m.print();
	//printf("%lu\n",sizeof(Matrix));

	//m.remMatrix();
	return 0;
}
void zeroVector(Vector * v){
	int x;
	for(x=0; x<v->length; x++){
		v->setPoint(x,0.0);
	}
}
void zeroVector(Vector4D * v){
	int i;
	for(i=0; i<4; i++){
		v->val[i] = 0;
	}
}
void zeroVector(Vector3D * v){
	int i;
	for(i=0; i<3; i++){
		v->val[i] = 0;
	}
}
void zeroVector(Vector2D * v){
	int i;
	for(i=0; i<2; i++){
		v->val[i] = 0;
	}
}
void zeroMatrix(Matrix * m){
	int x,y;
	for(x=0; x<m->cols; x++){
		for(y=0; y<m->rows; y++){
			m->setPoint(x,y,0.0);
		}
	}
}
void zeroMatrix(Matrix4D * m){
	int i;
	for(i=0; i<4; i++){
		zeroVector(&(m->vect[i]));
	}
}
void zeroMatrix(Matrix3D * m){
	int i;
	for(i=0; i<3; i++){
		zeroVector(&(m->vect[i]));
	}
}
void zeroMatrix(Matrix2D * m){
	int i;
	for(i=0; i<2; i++){
		zeroVector(&(m->vect[i]));
	}
}
void scaleVector(double s, Vector4D * v){
	int i;
	for(i=0; i<4; i++){
		v->val[i] *= s;
	}
}
void scaleVector(double s, Vector3D * v){
	int i;
	for(i=0; i<3; i++){
		v->val[i] *= s;
	}
}
void scaleVector(double s, Vector2D * v){
	int i;
	for(i=0; i<2; i++){
		v->val[i] *= s;
	}
}
void scaleMatrix(double s, Matrix4D * m){
	int i;
	for(i=0; i<4; i++){
		scaleVector(s, &(m->vect[i]));
	}
}
void scaleMatrix(double s, Matrix3D * m){
	int i;
	for(i=0; i<3; i++){
		scaleVector(s, &(m->vect[i]));
	}
}
void scaleMatrix(double s, Matrix2D * m){
	int i;
	for(i=0; i<2; i++){
		scaleVector(s, &(m->vect[i]));
	}
}
void setVector(double a, double b, double c, double d, Vector4D * v){
	v->val[0] = a;
	v->val[1] = b;
	v->val[2] = c;
	v->val[3] = d;
}
void setVector(double a, double b, double c, Vector3D * v){
	v->val[0] = a;
	v->val[1] = b;
	v->val[2] = c;
}
void setVector(double a, double b, Vector2D * v){
	v->val[0] = a;
	v->val[1] = b;
}
void setMatrix(Vector4D a, Vector4D b, Vector4D c, Vector4D d, Matrix4D * m){
	m->vect[0] = a;
	m->vect[1] = b;
	m->vect[2] = c;
	m->vect[3] = d;
}
void setMatrix(Vector3D a, Vector3D b, Vector3D c, Matrix3D * m){
	m->vect[0] = a;
	m->vect[1] = b;
	m->vect[2] = c;
}
void setMatrix(Vector2D a, Vector2D b, Matrix2D * m){
	m->vect[0] = a;
	m->vect[1] = b;
}
void setVector(double x, Vector * v){
	int i;
	for(i=0; i<v->length; i++){
		v->setPoint(i,x);
	}
}
void setVector(double x, Vector4D * v){
	int i;
	for(i=0; i<4; i++){
		v->val[i] = x;
	}
}
void setVector(double x, Vector3D * v){
	int i;
	for(i=0; i<3; i++){
		v->val[i] = x;
	}
}
void setVector(double x, Vector2D * v){
	int i;
	for(i=0; i<2; i++){
		v->val[i] = x;
	}
}
void setMatrix(double z, Matrix * m){
	int x,y;
	for(x=0; x<m->cols; x++){
		for(y=0; y<m->rows; y++){
			m->setPoint(x,y,z);
		}
	}
}
void setMatrix(double z, Matrix4D * m){
	int x,y;
	for(x=0; x<4; x++){
		for(y=0; y<4; y++){
			m->vect[x].val[y] = z;
		}
	}
}
void setMatrix(double z, Matrix3D * m){
	int x,y;
	for(x=0; x<3; x++){
		for(y=0; y<3; y++){
			m->vect[x].val[y] = z;
		}
	}
}
void setMatrix(double z, Matrix2D * m){
	int x,y;
	for(x=0; x<2; x++){
		for(y=0; y<2; y++){
			m->vect[x].val[y] = z;
		}
	}
}
void setMatrix(double a1,double b1,double c1,double d1,
			   double a2,double b2,double c2,double d2,
			   double a3,double b3,double c3,double d3,
			   double a4,double b4,double c4,double d4, Matrix4D * m){
	m->vect[0].val[0] = a1;
	m->vect[0].val[1] = a2;
	m->vect[0].val[2] = a3;
	m->vect[0].val[3] = a4;

	m->vect[1].val[0] = b1;
	m->vect[1].val[1] = b2;
	m->vect[1].val[2] = b3;
	m->vect[1].val[3] = b4;

	m->vect[2].val[0] = c1;
	m->vect[2].val[1] = c2;
	m->vect[2].val[2] = c3;
	m->vect[2].val[3] = c4;

	m->vect[3].val[0] = d1;
	m->vect[3].val[1] = d2;
	m->vect[3].val[2] = d3;
	m->vect[3].val[3] = d4;
}
void setMatrix(double a1,double b1,double c1,
			   double a2,double b2,double c2,
			   double a3,double b3,double c3, Matrix3D *m){
	m->vect[0].val[0] = a1;
	m->vect[0].val[1] = a2;
	m->vect[0].val[2] = a3;

	m->vect[1].val[0] = b1;
	m->vect[1].val[1] = b2;
	m->vect[1].val[2] = b3;

	m->vect[2].val[0] = c1;
	m->vect[2].val[1] = c2;
	m->vect[2].val[2] = c3;
}
void setMatrix(double a1,double b1,
			   double a2,double b2, Matrix2D * m){
	m->vect[0].val[0] = a1;
	m->vect[0].val[1] = a2;

	m->vect[1].val[0] = b1;
	m->vect[1].val[1] = b2;
}
bool equals(Vector v1, Vector v2){
	if(v1.length!=v2.length){
		return false;
	}
	int x;
	for(x=0; x<v1.length; x++){
		if(v1.getPoint(x) != v2.getPoint(x)){
			return false;
		}
	}
	return true;
}
bool equals(Vector4D v1, Vector4D v2){
	int i;
	for(i=0; i<4; i++){
		if(v1.val[i]!=v2.val[i]){
			return false;
		}
	}
	return true;
}
bool equals(Vector3D v1, Vector3D v2){
	int i;
	for(i=0; i<3; i++){
		if(v1.val[i]!=v2.val[i]){
			return false;
		}
	}
	return true;
}
bool equals(Vector2D v1, Vector2D v2){
	int i;
	for(i=0; i<2; i++){
		if(v1.val[i]!=v2.val[i]){
			return false;
		}
	}
	return true;
}
bool equals(Matrix m1, Matrix m2){
	if(!(m1.cols==m2.cols && m1.rows==m2.rows)){
		return false;
	}
	int x,y;
	for(x=0; x<m1.cols; x++){
		for(y=0; y<m1.rows; y++){
			if(m1.getPoint(x,y) != m2.getPoint(x,y)){
				return false;
			}
		}
	}
	return true;
}
bool equals(Matrix4D m1, Matrix4D m2){
	int x,y;
	for(x=0; x<4; x++){
		for(y=0; y<4; y++){
			if(m1.vect[x].val[y]!=m2.vect[x].val[y]){
				return false;
			}
		}
	}
	return true;
}
bool equals(Matrix3D m1, Matrix3D m2){
	int x,y;
	for(x=0; x<3; x++){
		for(y=0; y<3; y++){
			if(m1.vect[x].val[y]!=m2.vect[x].val[y]){
				return false;
			}
		}
	}
	return true;
}
bool equals(Matrix2D m1, Matrix2D m2){
	int x,y;
	for(x=0; x<2; x++){
		for(y=0; y<2; y++){
			if(m1.vect[x].val[y]!=m2.vect[x].val[y]){
				return false;
			}
		}
	}
	return true;
}
void toString(Vector4D v){
	printf("Vector4D -");
	int i;
	for(i=0; i<4; i++){
		printf("\n| %f |",v.val[i]);
	}
	printf("\n");
}
void toString(Vector3D v){
	printf("Vector3D -");
	int i;
	for(i=0; i<3; i++){
		printf("\n| %f |",v.val[i]);
	}
	printf("\n");
}
void toString(Vector2D v){
	printf("Vector2D -");
	int i;
	for(i=0; i<2; i++){
		printf("\n| %f |",v.val[i]);
	}
	printf("\n");
}
void toString(Matrix4D m){
	printf("Matrix4D -");
	int i;
	for(i=0; i<4; i++){
		if(i != 0 || i!= 3){
			printf("\n| %f, %f, %f, %f |",m.vect[0].val[i],m.vect[1].val[i],m.vect[2].val[i],m.vect[3].val[i]);
		}
		else{
			printf("\n- %f, %f, %f, %f -",m.vect[0].val[i],m.vect[1].val[i],m.vect[2].val[i],m.vect[3].val[i]);
		}
	}
	printf("\n");
}
void toString(Matrix3D m){
	printf("Matrix3D -");
	int i;
	for(i=0; i<3; i++){
		if(i != 0 || i!= 3){
			printf("\n| %f, %f, %f |",m.vect[0].val[i],m.vect[1].val[i],m.vect[2].val[i]);
		}
		else{
			printf("\n- %f, %f, %f -",m.vect[0].val[i],m.vect[1].val[i],m.vect[2].val[i]);
		}
	}
	printf("\n");
}
void toString(Matrix2D m){
	printf("Matrix2D -");
	int i;
	for(i=0; i<2; i++){
		printf("\n| %f, %f |",m.vect[0].val[i],m.vect[1].val[i]);
	}
	printf("\n");
}

Vector4D add(Vector4D v1, Vector4D v2){
	Vector4D out;
	int i;
	for(i=0; i<4; i++){
		out.val[i] = v1.val[i] + v2.val[i];
	}
	return out;
}
Vector3D add(Vector3D v1, Vector3D v2){
	Vector3D out;
	int i;
	for(i=0; i<3; i++){
		out.val[i] = v1.val[i] + v2.val[i];
	}
	return out;
}
Vector2D add(Vector2D v1, Vector2D v2){
	Vector2D out;
	int i;
	for(i=0; i<2; i++){
		out.val[i] = v1.val[i] + v2.val[i];
	}
	return out;
}

Vector4D linearTransformation(Vector4D input, Matrix4D basisTrans){
	Vector4D basisX = basisTrans.vect[0];
	Vector4D basisY = basisTrans.vect[1];
	Vector4D basisZ = basisTrans.vect[2];
	Vector4D basisA = basisTrans.vect[3];
	
	scaleVector(input.val[0], &basisX);
	scaleVector(input.val[1], &basisY);
	scaleVector(input.val[2], &basisZ);
	scaleVector(input.val[3], &basisA);

	return add(add(basisX, basisY),add(basisZ, basisA));
}
Vector3D linearTransformation(Vector3D input, Matrix3D basisTrans){
	Vector3D basisX = basisTrans.vect[0];
	Vector3D basisY = basisTrans.vect[1];
	Vector3D basisZ = basisTrans.vect[2];
	
	scaleVector(input.val[0], &basisX);
	scaleVector(input.val[1], &basisY);
	scaleVector(input.val[2], &basisZ);

	return add(add(basisX, basisY),basisZ);
}
Vector2D linearTransformation(Vector2D input, Matrix2D basisTrans){
	Vector2D basisX = basisTrans.vect[0];
	Vector2D basisY = basisTrans.vect[1];
	
	scaleVector(input.val[0], &basisX);
	scaleVector(input.val[1], &basisY);

	return add(basisX, basisY);
}

void transpose(Matrix4D * m){
	//Swap elements
	double temp = 0;
	int x,y;
	for(x=0; x<4-1; x++){
		for(y=x+1; y<4; y++){
			temp = m->vect[x].val[y];
			m->vect[x].val[y] = m->vect[y].val[x];
			m->vect[y].val[x] = temp;
		}
	}
}
void transpose(Matrix3D * m){
	//Swap elements
	double temp = 0;
	int x,y;
	for(x=0; x<3-1; x++){
		for(y=x+1; y<3; y++){
			temp = m->vect[x].val[y];
			m->vect[x].val[y] = m->vect[y].val[x];
			m->vect[y].val[x] = temp;
		}
	}
}
void transpose(Matrix2D * m){
	//Swap elements
	double temp = 0;
	int x,y;
	for(x=0; x<2-1; x++){
		for(y=x+1; y<2; y++){
			temp = m->vect[x].val[y];
			m->vect[x].val[y] = m->vect[y].val[x];
			m->vect[y].val[x] = temp;
		}
	}

}

void rotateVector(Vector4D * v, double degXY, double degYZ, double degXZ){
	Matrix4D rotationBasis;
	//NOTE: DOES NOT WORK... NEED TO IMPLIEMENT
	setMatrix(1,0,0,0,
			  0,1,0,0,
			  0,0,1,0,
			  0,0,0,1,&rotationBasis);
}
void rotateVector(Vector3D * v, double degXY, double degYZ, double degXZ){
	Matrix3D rotationBasis;
	//NOTE: DOES NOT WORK... NEED TO IMPLIEMENT
	setMatrix(1,0,0,
			  0,1,0,
			  0,0,1,&rotationBasis);
}
void rotateVector(Vector2D * v, double degXY){
	Matrix2D rotationBasis;
	setMatrix(cos(degXY),-sin(degXY),
			  sin(degXY),cos(degXY),&rotationBasis);
	*v = linearTransformation(*v, rotationBasis);
}

double toDeg(double rad){
	return 180/PI * rad;
}
double toRad(double deg){
	return PI/180 * deg;
}

Matrix4D multiply(Matrix4D m1, Matrix4D m2){
	Vector4D outX = linearTransformation(m2.vect[0], m1);
	Vector4D outY = linearTransformation(m2.vect[1], m1);
	Vector4D outZ = linearTransformation(m2.vect[2], m1);
	Vector4D outA = linearTransformation(m2.vect[3], m1);
	
	Matrix4D outMatrix;
	setMatrix(outX,outY,outZ,outA,&outMatrix);
	return outMatrix;
}
Matrix3D multiply(Matrix3D m1, Matrix3D m2){
	Vector3D outX = linearTransformation(m2.vect[0], m1);
	Vector3D outY = linearTransformation(m2.vect[1], m1);
	Vector3D outZ = linearTransformation(m2.vect[2], m1);
	
	Matrix3D outMatrix;
	setMatrix(outX,outY,outZ,&outMatrix);
	return outMatrix;
}
Matrix2D multiply(Matrix2D m1, Matrix2D m2){
	Vector2D outI = linearTransformation(m2.vect[0], m1);
	Vector2D outJ = linearTransformation(m2.vect[1], m1);

	Matrix2D outMatrix;
	setMatrix(outI,outJ,&outMatrix);
	return outMatrix;
}
Matrix3D subMatrix(int col, int row, Matrix4D in){
	Matrix3D out;

	int offsetX = 0,offsetY = 0;
	int x,y;
	for(x=0; x<4; x++){
		if(x == col){
				offsetX = 1;
		}
		else{
			for(y=0; y<4; y++){
				if(y == row){
					offsetY = 1;
				}
				else{
					out.vect[x-offsetX].val[y-offsetY] = in.vect[x].val[y];
				}
			}
		}
		offsetY = 0;
	}

	return out;
}
Matrix2D subMatrix(int col, int row, Matrix3D in){
	Matrix2D out;

	int offsetX = 0,offsetY = 0;
	int x,y;
	for(x=0; x<3; x++){
		if(x == col){
				offsetX = 1;
		}
		else{
			for(y=0; y<3; y++){
				if(y == row){
					offsetY = 1;
				}
				else{
					//printf("col: %d, row: %d\n",x,y);
					//printf("val being set: %f at: (%d, %d)\n",in.vect[x].val[y],x-offsetX,y-offsetY);
					out.vect[x-offsetX].val[y-offsetY] = in.vect[x].val[y];
				}
			}
		}
		offsetY = 0;
	}

	return out;
}
Vector4D getRow(int row, Matrix4D m){
	Vector4D out;
	int i;
	for(i=0; i<4; i++){
		out.val[i] = m.vect[i].val[row];
	}
	return out;
}
Vector3D getRow(int row, Matrix3D m){
	Vector3D out;
	int i;
	for(i=0; i<3; i++){
		out.val[i] = m.vect[i].val[row];
	}
	return out;
}
Vector2D getRow(int row, Matrix2D m){
	Vector2D out;
	int i;
	for(i=0; i<2; i++){
		out.val[i] = m.vect[i].val[row];
	}
	return out;
}
double det(Matrix4D m){
	return m.vect[0].val[0]*det(subMatrix(0,0,m))-m.vect[1].val[0]*det(subMatrix(1,0,m))+m.vect[2].val[0]*det(subMatrix(2,0,m))-m.vect[3].val[0]*det(subMatrix(3,0,m));
}
double det(Matrix3D m){
	return m.vect[0].val[0]*det(subMatrix(0,0,m))-m.vect[1].val[0]*det(subMatrix(1,0,m))+m.vect[2].val[0]*det(subMatrix(2,0,m));
}
double det(Matrix2D m){
	//ad-bc
	return m.vect[0].val[0]*m.vect[1].val[1] - m.vect[1].val[0]*m.vect[0].val[1];
}

void rowOPAdd(int row, Matrix4D * m, Vector4D vect){
	int i;
	for(i=0; i<4; i++){
		m->vect[i].val[row] += vect.val[i];
	}
}
void rowOPSub(int row, Matrix4D * m, Vector4D vect){
	int i;
	for(i=0; i<4; i++){
		m->vect[i].val[row] -= vect.val[i];
	}
}
void rowOPMult(int row, Matrix4D * m, double s){
	int i;
	for(i=0; i<4; i++){
		m->vect[i].val[row] *= s;
	}
}
void rowOPDiv(int row, Matrix4D * m, double s){
	int i;
	for(i=0; i<4; i++){
		m->vect[i].val[row] /= s;
	}
}
void rowOPSwap(int row1, int row2, Matrix4D * m){
	Vector4D temp;
	int i;
	for(i=0; i<4; i++){
		temp.val[i] = m->vect[i].val[row1];
	}
	for(i=0; i<4; i++){
		m->vect[i].val[row1] = m->vect[i].val[row2];
	}
	for(i=0; i<4; i++){
		m->vect[i].val[row2] = temp.val[i];
	}
}
void rowOPAdd(int row, Matrix3D * m, Vector3D vect){
	int i;
	for(i=0; i<3; i++){
		m->vect[i].val[row] += vect.val[i];
	}
}
void rowOPSub(int row, Matrix3D * m, Vector3D vect){
	int i;
	for(i=0; i<3; i++){
		m->vect[i].val[row] -= vect.val[i];
	}
}
void rowOPMult(int row, Matrix3D * m, double s){
	int i;
	for(i=0; i<3; i++){
		m->vect[i].val[row] *= s;
	}
}
void rowOPDiv(int row, Matrix3D * m, double s){
	int i;
	for(i=0; i<3; i++){
		m->vect[i].val[row] /= s;
	}
}
void rowOPSwap(int row1, int row2, Matrix3D * m){
	Vector3D temp;
	int i;
	for(i=0; i<3; i++){
		temp.val[i] = m->vect[i].val[row1];
	}
	for(i=0; i<3; i++){
		m->vect[i].val[row1] = m->vect[i].val[row2];
	}
	for(i=0; i<3; i++){
		m->vect[i].val[row2] = temp.val[i];
	}
}
void rowOPAdd(int row, Matrix2D * m, Vector2D vect){
	int i;
	for(i=0; i<2; i++){
		m->vect[i].val[row] += vect.val[i];
	}
}
void rowOPSub(int row, Matrix2D * m, Vector2D vect){
	int i;
	for(i=0; i<2; i++){
		m->vect[i].val[row] -= vect.val[i];
	}
}
void rowOPMult(int row, Matrix2D * m, double s){
	int i;
	for(i=0; i<2; i++){
		if(m->vect[i].val[row]!=0){
			m->vect[i].val[row] *= s;
		}
	}
}
void rowOPDiv(int row, Matrix2D * m, double s){
	int i;
	for(i=0; i<2; i++){
		if(m->vect[i].val[row]!=0){
			m->vect[i].val[row] /= s;
		}
	}
}
void rowOPSwap(int row1, int row2, Matrix2D * m){
	Vector2D temp;
	int i;
	for(i=0; i<2; i++){
		temp.val[i] = m->vect[i].val[row1];
	}
	for(i=0; i<2; i++){
		m->vect[i].val[row1] = m->vect[i].val[row2];
	}
	for(i=0; i<2; i++){
		m->vect[i].val[row2] = temp.val[i];
	}
}
/*
void REF(Matrix * m){
	Matrix zeroMat;
	zeroMatrix(&zeroMat);
	//STEP 1: check to make sure it is not the zero matrix
	if(!equals(*m, zeroMat)){
		Vector zeroVect;
		zeroVector(&zeroVect);
		//STEP 2: Start at the first non-zero column and swap first row to top
		int x,y;
		for(x=0; x<4; x++){
			//first col
			if(!equals(m->vect[x],zeroVect)){
				break;
			}
		}
		for(y=0; y<4; y++){
			//first row
			if(m->vect[x].val[y]!=0){
				break;
			}
		}
		if(y!=0){
			rowOPSwap(0,y,m);
		}
		//STEP 3: Mult row by 1/a
		//printf("1/a = %f\n",(1./(m->vect[i].val[0])));
		rowOPMult(0,m,(1./(m->vect[x].val[0])));
		//STEP 4: Remove the constants under a
		int i;
		for(i=1; i<4; i++){
			Vector4D remVect = getRow(0,*m);
			scaleVector(m->vect[x].val[i],&remVect);
			rowOPSub(i,m,remVect);
		}
		//STEP 5: Repeat steps 1-4 on remaining rows
		Matrix3D remMat = subMatrix(0,0,*m);
		REF(&remMat);
		//reinsert matrix
		for(x=1; x<4; x++){
			for(y=1; y<4; y++){
				m->vect[x].val[y] = remMat.vect[x-1].val[y-1];
			}
		}

		//DONE
	}
}*/
void REF(Matrix4D * m){
	Matrix4D zeroMat;
	zeroMatrix(&zeroMat);
	//STEP 1: check to make sure it is not the zero matrix
	if(!equals(*m, zeroMat)){
		Vector4D zeroVect;
		zeroVector(&zeroVect);
		//STEP 2: Start at the first non-zero column and swap first row to top
		int x,y;
		for(x=0; x<4; x++){
			//first col
			if(!equals(m->vect[x],zeroVect)){
				break;
			}
		}
		for(y=0; y<4; y++){
			//first row
			if(m->vect[x].val[y]!=0){
				break;
			}
		}
		if(y!=0){
			rowOPSwap(0,y,m);
		}
		//STEP 3: Mult row by 1/a
		//printf("1/a = %f\n",(1./(m->vect[i].val[0])));
		rowOPMult(0,m,(1./(m->vect[x].val[0])));
		//STEP 4: Remove the constants under a
		int i;
		for(i=1; i<4; i++){
			Vector4D remVect = getRow(0,*m);
			scaleVector(m->vect[x].val[i],&remVect);
			rowOPSub(i,m,remVect);
		}
		//STEP 5: Repeat steps 1-4 on remaining rows
		Matrix3D remMat = subMatrix(0,0,*m);
		REF(&remMat);
		//reinsert matrix
		for(x=1; x<4; x++){
			for(y=1; y<4; y++){
				m->vect[x].val[y] = remMat.vect[x-1].val[y-1];
			}
		}

		//DONE
	}
}
void REF(Matrix3D * m){
	Matrix3D zeroMat;
	zeroMatrix(&zeroMat);
	//STEP 1: check to make sure it is not the zero matrix
	if(!equals(*m, zeroMat)){
		Vector3D zeroVect;
		zeroVector(&zeroVect);
		//STEP 2: Start at the first non-zero column and swap first row to top
		int x,y;
		for(x=0; x<3; x++){
			//first col
			if(!equals(m->vect[x],zeroVect)){
				break;
			}
		}
		for(y=0; y<3; y++){
			//first row
			if(m->vect[x].val[y]!=0){
				break;
			}
		}
		if(y!=0){
			rowOPSwap(0,y,m);
		}
		//STEP 3: Mult row by 1/a
		//printf("1/a = %f\n",(1./(m->vect[i].val[0])));
		rowOPMult(0,m,(1./(m->vect[x].val[0])));
		//STEP 4: Remove the constants under a
		int i;
		for(i=1; i<3; i++){
			Vector3D remVect = getRow(0,*m);
			scaleVector(m->vect[x].val[i],&remVect);
			rowOPSub(i,m,remVect);
		}
		//STEP 5: Repeat steps 1-4 on remaining rows
		Matrix2D remMat = subMatrix(0,0,*m);
		REF(&remMat);
		//reinsert matrix
		for(x=1; x<3; x++){
			for(y=1; y<3; y++){
				m->vect[x].val[y] = remMat.vect[x-1].val[y-1];
			}
		}
		//DONE
	}
}
void REF(Matrix2D * m){
	Matrix2D zeroMat;
	zeroMatrix(&zeroMat);
	//STEP 1: check to make sure it is not the zero matrix
	if(!equals(*m, zeroMat)){
		Vector2D zeroVect;
		zeroVector(&zeroVect);
		//STEP 2: Start at the first non-zero column and swap first row to top
		int x,y;
		for(x=0; x<2; x++){
			//first col
			if(!equals(m->vect[x],zeroVect)){
				break;
			}
		}
		for(y=0; y<2; y++){
			//first row
			if(m->vect[x].val[y]!=0){
				break;
			}
		}
		if(y!=0){
			rowOPSwap(0,y,m);
		}
		//STEP 3: Mult row by 1/a
		//printf("1/a = %f\n",(1./(m->vect[x].val[0])));
		rowOPMult(0,m,(1./(m->vect[x].val[0])));
		//STEP 4: Remove the constants under a
		int i;
		for(i=1; i<2; i++){
			Vector2D remVect = getRow(0,*m);
			scaleVector(m->vect[x].val[i],&remVect);
			rowOPSub(i,m,remVect);
		}
		//STEP 5: Repeat steps 1-4 on remaining row
		if(m->vect[1].val[1]!=0){
			m->vect[1].val[1] = 1;
		}
	}
}

int rank(Matrix4D m){
	int out = 4;
	Matrix4D REFMat = m;
	REF(&REFMat);

	Vector4D zeroVect;
	zeroVector(&zeroVect);
	int i;
	for(i=0; i<4; i++){
		if(equals(zeroVect,getRow(i,REFMat))){
			out--;
		}
	}
	return out;
}
int rank(Matrix3D m){
	int out = 3;
	Matrix3D REFMat = m;
	REF(&REFMat);

	Vector3D zeroVect;
	zeroVector(&zeroVect);
	int i;
	for(i=0; i<3; i++){
		if(equals(zeroVect,getRow(i,REFMat))){
			out--;
		}
	}
	return out;
}
int rank(Matrix2D m){
	int out = 2;
	Matrix2D REFMat = m;
	REF(&REFMat);

	Vector2D zeroVect;
	zeroVector(&zeroVect);
	int i;
	for(i=0; i<2; i++){
		if(equals(zeroVect,getRow(i,REFMat))){
			out--;
		}
	}
	return out;
}
int dotProduct(Vector4D v1, Vector4D v2){
	int i, out = 0;
	for(i=0; i<4; i++){
		out += v1.val[i]*v2.val[i];
	}
	return out;
}
int dotProduct(Vector3D v1, Vector3D v2){
	int i, out = 0;
	for(i=0; i<3; i++){
		out += v1.val[i]*v2.val[i];
	}
	return out;
}
int dotProduct(Vector2D v1, Vector2D v2){
int i, out = 0;
	for(i=0; i<2; i++){
		out += v1.val[i]*v2.val[i];
	}
	return out;
}

Vector3D crossProduct(Vector3D v1, Vector3D v2){
	Matrix3D mat;
	setMatrix(1.0,&mat);
	mat.vect[1] = v1;
	mat.vect[2] = v2;

	Vector3D out;
	out.val[0] = det(subMatrix(0,0,mat));
	out.val[1] = det(subMatrix(0,1,mat));
	out.val[2] = det(subMatrix(0,2,mat));
	return out;
}
int crossProduct(Vector2D v1, Vector2D v2){
	Matrix2D mat;
	mat.vect[0] = v1;
	mat.vect[1] = v2;
	return det(mat);
}

Matrix4D to4DMatrix(Matrix m){
	Matrix4D out;
	if(m.cols==4 && m.rows == 4){
		int x,y;
		for(x=0; x<4; x++){
			for(y=0; y<4; y++){
				out.vect[x].val[y] = m.getPoint(x,y);
			}
		}
	}
	else{
		zeroMatrix(&out);
	}
	return out;
}
Matrix3D to3DMatrix(Matrix m){
	Matrix3D out;
	if(m.cols==3 && m.rows == 3){
		int x,y;
		for(x=0; x<3; x++){
			for(y=0; y<3; y++){
				out.vect[x].val[y] = m.getPoint(x,y);
			}
		}
	}
	else{
		zeroMatrix(&out);
	}
	return out;
}
Matrix2D to2DMatrix(Matrix m){
	Matrix2D out;
	if(m.cols==2 && m.rows == 2){
		int x,y;
		for(x=0; x<2; x++){
			for(y=0; y<2; y++){
				out.vect[x].val[y] = m.getPoint(x,y);
			}
		}
	}
	else{
		zeroMatrix(&out);
	}
	return out;
}

Matrix toMatrix(Matrix4D m){
	Matrix out;
	out.setSize(4,4);
	int x,y;
	for(x=0; x<4; x++){
		for(y=0; y<4; y++){
			out.setPoint(x,y,m.vect[x].val[y]);
		}
	}
	return out;
}
Matrix toMatrix(Matrix3D m){
	Matrix out;
	out.setSize(3,3);
	int x,y;
	for(x=0; x<3; x++){
		for(y=0; y<3; y++){
			out.setPoint(x,y,m.vect[x].val[y]);
		}
	}
	return out;
}
Matrix toMatrix(Matrix2D m){
	Matrix out;
	out.setSize(2,2);
	int x,y;
	for(x=0; x<2; x++){
		for(y=0; y<2; y++){
			out.setPoint(x,y,m.vect[x].val[y]);
		}
	}
	return out;
}



