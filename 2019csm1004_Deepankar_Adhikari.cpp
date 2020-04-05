#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <bits/stdc++.h>
using namespace std;
int globalAlpha = 2;//SIZE OF LEAF NODES
//vector[][0] has pointID; vector[][1] has xCoordinate; vector[][2] has yCoordinate
bool sortWithRespectToX(const vector<int>& v1, const vector<int>& v2){
    return v1[1]<v2[1];
}
bool sortWithRespectToY(const vector<int>& v1, const vector<int>& v2){
    return v1[2]<v2[2];
}

struct internalNode{
    struct internalNode* left;
    struct internalNode* right;
    int isLeftOrRight; // at root its goona be 0 for if its left its -1 and if its right its 1 if unassigned then -2
    struct internalNode* parent;
    int line;   // IF IT AINT ASSIGNED ANY LINE ITS VALUE SHOULD BE -2 , iF ITS HORIZONTAL THEN 0 IF VERTICAL THEN 1
  // not taking it for now dont know if i should  struct point pointID;
    vector<int> FX;    // FIRST POINT ORDERED BY X COORDINATES
    vector<int> LX;    //LAST POINT ORDERED BY X COORDINATES
    vector<int> BY;    //BOTTOM POINT ORDERED BY Y COORDINATE
    vector<int> TY;    //TOP POINT ORDERED BY Y COORDINATES
    int size;       //SIZE OF THE VECTOR OR UNDERLYING NODES
    bool isTerminal;    // TRUE IS ITS A TERMINAL NODE AND ON SCAN IF WE SEE THIS TRUE WE ASSUME THAT IT ACTUALLY IS SIMPLY THE LEAF DEFINED IN THE NEXT LINE
    vector<vector<int>> leaf; //IF isTerminal SET TRUE THEN THIS LEAF HOLDS THE SIGNIFICANCE OF HOLDING THE DATA NODES
    // thought of adding the node vector by which it divides
    vector<int> information;
};

struct internalNode* createInternalNode(struct internalNode* left, struct internalNode* right, int isLeftOrRight, struct internalNode* parent, int line, vector<int> FX, vector<int> LX, vector<int> BY, vector<int> TY, int size, bool isTerminal, vector<vector<int>> leaf, vector<int>information){
    struct internalNode* newInternal = new internalNode;
    newInternal->left = left;
    newInternal->right = right;
    newInternal->isLeftOrRight = isLeftOrRight;
    newInternal->parent = parent;
    newInternal->line = line;
    newInternal->FX = FX;
    newInternal->LX = LX;
    newInternal->BY = BY;
    newInternal->TY = TY;
    newInternal->size = size;
    newInternal->isTerminal = isTerminal;
    newInternal->leaf = leaf;
    newInternal->information = information;

    return newInternal;
}



//myVectorX and myVectorY are vectors sorted with respect to x and y axis respectively
struct internalNode* createTree(vector<vector<int>> myVectorX, vector<vector<int>> myVectorY, struct internalNode* node,int isLeftOrRight){
    if(myVectorX.size()<= globalAlpha){
    //for terminal nodes  in the information part of the internalNode structure I am storing the first node
      struct internalNode* newNode = createInternalNode(NULL,NULL,isLeftOrRight,node,-2, myVectorX[0], myVectorX[myVectorX.size()-1],myVectorY[0], myVectorY[myVectorY.size()-1], myVectorX.size(), 1 , myVectorX, myVectorX[0] );
       if(node==NULL){
            return newNode;
       }else if(node!= NULL){
            if(newNode == node->left){
                newNode->isLeftOrRight = -1;
            }else if(newNode == node->right){
                newNode->isLeftOrRight = 1;
            }
            return newNode;
       }
    }else if(myVectorX.size() > globalAlpha){
        int size = myVectorX.size();
        vector<int> FX  = myVectorX[0];
        vector<int> LX = myVectorX[size-1];
        int differenceInX = LX[1] - FX[1]; //FX is the first vectorNode in myVectorX; its 1 index holds x coordinates myVectorX[0][1]

        vector<int> BY  = myVectorY[0];
        vector<int> TY = myVectorY[size-1];
        int differenceInY = TY[2] - BY[2]; //FX is the first vectorNode in myVectorX; its 1 index holds x coordinates myVectorX[0][1]
//dividing by vertical axis condition
        if(differenceInX>=differenceInY){//Dividing by Vertical axis

            struct internalNode* newNode = createInternalNode(NULL,NULL,isLeftOrRight,node,1, FX, LX,BY,TY,size, 0 , myVectorX,myVectorX[0] );




            int mid = (size-1)/2;
            newNode->information= myVectorX[mid];
            vector<vector<int>> leftVectorX; // for KEEPING TRACK OF ELEMENTS ON LEFT OF THE LINE
            vector<vector<int>> leftVectorY; // to be sorted afterwards
            //for copying the vector into a new above vectors
            int i,x,y,z;
            for(i=0;i<=mid;i++){ // copying vector
                x = myVectorX[i][0];
                y = myVectorX[i][1];
                z = myVectorX[i][2];
                vector<int> temp;

                temp.push_back(x);
                temp.push_back(y);
                temp.push_back(z);
                leftVectorX.push_back(temp);
                leftVectorY.push_back(temp);
            }
            sort(leftVectorY.begin(),leftVectorY.end(),sortWithRespectToY);
            newNode->left = createTree(leftVectorX,leftVectorY,newNode,-1);

            int sizeRight = size-mid-1;
            vector<vector<int>> rightVectorX;
            vector<vector<int>> rightVectorY;
            for(i=mid+1;i<=size-1;i++){ // copying vector
                x = myVectorX[i][0];
                y = myVectorX[i][1];
                z = myVectorX[i][2];
                vector<int> temp;

                temp.push_back(x);
                temp.push_back(y);
                temp.push_back(z);
                rightVectorX.push_back(temp);
                rightVectorY.push_back(temp);
            }
            sort(rightVectorY.begin(),rightVectorY.end(),sortWithRespectToY);
            newNode->right = createTree(rightVectorX,rightVectorY,newNode,1);

return newNode;
//dividing by horizontal line condition
        }else if(differenceInY>differenceInX){//dividing by horizontal axis

           struct internalNode* newNode = createInternalNode(NULL,NULL,isLeftOrRight,node,0, FX, LX,BY,TY,size, 0 , myVectorY, myVectorY[0] );


            int mid = (size-1)/2;
            newNode->information = myVectorY[mid];
            vector<vector<int>> bottomVectorX; // for KEEPING TRACK OF ELEMENTS ON LEFT OF THE LINE
            vector<vector<int>> bottomVectorY; // to be sorted afterwards
            //for copying the vector into a new above vectors

            int i,x,y,z;
            for(i=0;i<=mid;i++){ // copying vector
                x = myVectorY[i][0];
                y = myVectorY[i][1];
                z = myVectorY[i][2];
                vector<int> temp;
                temp.push_back(x);
                temp.push_back(y);
                temp.push_back(z);
                bottomVectorY.push_back(temp);
                bottomVectorX.push_back(temp);
            }
            sort(bottomVectorX.begin(),bottomVectorX.end(),sortWithRespectToX);
            newNode->left = createTree(bottomVectorX,bottomVectorY,newNode,-1);

            int sizeTop = size-mid-1;
            vector<vector<int>> topVectorX;
            vector<vector<int>> topVectorY;
            for(i=mid+1;i<=size-1;i++){ // copying vector
                x = myVectorY[i][0];
                y = myVectorY[i][1];
                z = myVectorY[i][2];
                vector<int> temp;

                temp.push_back(x);
                temp.push_back(y);
                temp.push_back(z);
                topVectorY.push_back(temp);
                topVectorX.push_back(temp);
            }
            sort(topVectorX.begin(),topVectorX.end(),sortWithRespectToX);
            newNode->right = createTree(topVectorX,topVectorY,newNode,1);
return newNode;
        }


    }


}
// DONE WITH CONSTRUCTING THE TREE

// FUNCTION TO SEE IF THE GIVEN POINT LIES IN MY KD TREE
bool searchMyPoint(struct internalNode* root, vector<int>myPoint){
    if(root==NULL){
        return 0;
    }
    bool temp = false;
    int i;
    if(root->isTerminal == true){
        for(i=0;i<root->size;i++){
            if(root->leaf[i]==myPoint){
                temp = true;
            }
        }
     return temp;
    }
    if(root->isTerminal == false){
         //IF THE NODE IS NOT A TERMINAL NODE AND DIVIDES BY VERICAL LINE
                //search in the structure of the children and go to side which has it


            if(find(root->left->leaf.begin(), root->left->leaf.end(), myPoint)!= root->left->leaf.end()){

                return searchMyPoint(root->left,myPoint);
            }
            if(find(root->right->leaf.begin(), root->right->leaf.end(), myPoint)!= root->right->leaf.end()){
                return searchMyPoint(root->right,myPoint);
            }
            else
                return false;

    }
}


//FUNCTION TO INSERT A NEW POINT; (HOLDING POINT ID ,X AND Y COORDINATES) IN THE KD TREE
struct internalNode* updateNode(struct internalNode* root,vector<int>newPoint){
    if(root->isTerminal==false){
        root->leaf.push_back(newPoint); // leaf stores all the points under that region
    root->size = root->size + 1;
        //UPDATING EXTREMITIES IF REQUIRED
        if(newPoint[1] < root->FX[1]){
            root->FX = newPoint;
        }
        if(newPoint[1] > root->LX[1]){
            root->LX = newPoint;
        }
        if(newPoint[2] > root->TY[2]){
            root->TY = newPoint;
        }
        if(newPoint[2] < root->BY[2]){
            root->BY = newPoint;
        }
        return root;
    }else if(root->isTerminal==true && root->size < globalAlpha){
        root->leaf.push_back(newPoint); // leaf stores all the points under that region
    root->size = root->size + 1;
        //UPDATING EXTREMITIES IF REQUIRED
        if(newPoint[1] < root->FX[1]){
            root->FX = newPoint;
        }
        if(newPoint[1] > root->LX[1]){
            root->LX = newPoint;
        }
        if(newPoint[2] > root->TY[2]){
            root->TY = newPoint;
        }
        if(newPoint[2] < root->BY[2]){
            root->BY = newPoint;
        }
    return root;
    }else if(root->isTerminal == true && root->size >= globalAlpha){
        root->leaf.push_back(newPoint); // leaf stores all the points under that region //following 1 line added afterwards
        vector<vector<int>> endLeafX = root->leaf; // leaf stores the elements and one time we sort it with respect to x axis
        vector<vector<int>> endLeafY = root->leaf; // leaf stores the elements and one time we sort it with respect to y axis
        sort(endLeafX.begin(),endLeafX.end(),sortWithRespectToX);
        sort(endLeafY.begin(),endLeafY.end(),sortWithRespectToY);
        //root;
struct internalNode* forFree = root;

        struct internalNode* newRoot = NULL;
        newRoot=createTree(endLeafX,endLeafY,newRoot,0);
        if(root->parent == NULL){
            root = newRoot; // problem of scope root not getting returned
            return root;
        }else{
            if(root->isLeftOrRight == -1){
                newRoot->parent = root->parent;
                root->parent->left = newRoot;
free(forFree);//maybe
                return newRoot;
            }else if(root->isLeftOrRight == 1){
                newRoot->parent = root->parent;
                root->parent->right = newRoot;

                return newRoot;
            }
        }

       /* int diffX = endLeafX[endLeafX.size()-1][1] - endLeafX[0][1];
        int diffY = endLeafY[endLeafY.size()-1][1] - endLeafY[0][1];
        if(diffX>=diffY){
            I thought about creating create tree function

        }*/
    return root;
    }
};
struct internalNode* insertIntoKD(struct internalNode* root, vector<int>newPoint){
    if(root==NULL){
            struct internalNode* newNode = createInternalNode(NULL,NULL,0,NULL,-2, newPoint, newPoint,newPoint, newPoint, 1, 1 ,{newPoint}, newPoint );
            return newNode;
    }

    if(root->isTerminal== true && root->size < globalAlpha){
            root = updateNode(root,newPoint);
            return root;
    }
    if(root->isTerminal == true && root->size == globalAlpha){
            root = updateNode(root,newPoint);

//not returning the node
            return root;
    }
    if(root->isTerminal == false ){
        root = updateNode(root,newPoint);//update that current point

        if(root->line == 1){
            if(root->information[1] < newPoint[1]){
                root->right = insertIntoKD(root->right, newPoint);
            }else if(root->information[1] >= newPoint[1]){
                root->left = insertIntoKD(root->left, newPoint);
            }
        }else if(root->line == 0){
            if(root->information[2] < newPoint[2]){
                root->right = insertIntoKD(root->right, newPoint);
            }else if(root->information[2] >= newPoint[2]){
                root->left = insertIntoKD(root->left, newPoint);
            }
        }
        return root;
    }
}

// CODE TO DO THE LEVEL ORDER VISUALIZATION
void printLevelOrder(internalNode *root)
{

    if (root == NULL){
        cout<<"Empty is the tree";
        return;
    }

    queue<internalNode*> q;
    q.push(root);

    while (q.empty() == false)
    {
        int nodeCount = q.size();

        while (nodeCount > 0)
        {
            internalNode *node = q.front();
            if(node->isTerminal == false){
            if(node->line == 1){
                cout<<" vertical line on point";
            }
            if(node->line == 0){
                cout<<" Horizontal line on point";
            }
            cout << " with node id: "<< node->information[0]<<",x-coordinate: "<<node->information[1]<<",y-coordinate: "<<node->information[2]<<endl;
            }
            q.pop();
            if (node->left != NULL)
                q.push(node->left);
            if (node->right != NULL)
                q.push(node->right);
            nodeCount--;
        }
        cout << endl;
    }
}
void printLevelOrderWithLeaves(internalNode *root)
{

    if (root == NULL){
        cout<<"Empty is the tree";
        return;
    }

    queue<internalNode*> q;
    q.push(root);

    while (q.empty() == false)
    {
        int nodeCount = q.size();

        while (nodeCount > 0)
        {
            internalNode *node = q.front();
            if(node->isTerminal == false){
            if(node->line == 1){
                cout<<" vertical line on point";
            }
            if(node->line == 0){
                cout<<" Horizontal line on point";
            }
            cout << " with node id: "<< node->information[0]<<",x-coordinate: "<<node->information[1]<<",y-coordinate: "<<node->information[2]<<endl;
            }
            //new Addition
            if(node->isTerminal == true){
                    int i;
            for(i=0;i<node->leaf.size();i++){
            cout << " leaf with node id: "<< node->leaf[i][0]<<",x-coordinate: "<<node->leaf[i][1]<<",y-coordinate: "<<node->leaf[i][2]<<endl;
            }
            }
            q.pop();
            if (node->left != NULL)
                q.push(node->left);
            if (node->right != NULL)
                q.push(node->right);
            nodeCount--;
        }
        cout << endl;
    }
}
//end of printLevel order
//i believe region could be given by 2 points which are diagonally opposite extremities
//regionPoint1 stores lower parts of diagonal
bool pointInside(internalNode* root,vector<int>point, vector<int>regionPoint1, vector<int>regionPoint2){
        bool isThere = false;
        if(point[1]>=regionPoint1[0] && point[1]<=regionPoint2[0]){
            if(point[2]>=regionPoint1[1] && point[2]<=regionPoint2[1]){
                if(searchMyPoint(root,point)){
                    isThere = true;
                }
            }
        }
        return isThere;
}





int main(){
int i =0;
int j;
int pid, xid, yid;
int r=1000;
int c=3;
ifstream f;
vector<vector<int>>points;
f.open("points.txt");

vector<int> row;

while(f>>pid>>xid>>yid){
   points.push_back(vector<int>());
   points[i].push_back(pid);
   points[i].push_back(xid);
   points[i].push_back(yid);
   i++;
}




            vector<vector<int>> myVectorX; // for KEEPING TRACK OF ELEMENTS ON LEFT OF THE LINE
            vector<vector<int>> myVectorY; // to be sorted afterwards
            //for copying the vector into a new above vectors


            int x,y,z;
            for(i=0;i<points.size();i++){ // copying vector
                x = points[i][0];
                y = points[i][1];
                z = points[i][2];
                vector<int> temp;
                temp.push_back(x);
                temp.push_back(y);
                temp.push_back(z);
                myVectorX.push_back(temp);
                myVectorY.push_back(temp);
            }
            sort(myVectorX.begin(),myVectorX.end(),sortWithRespectToX);
            sort(myVectorY.begin(),myVectorY.end(),sortWithRespectToY);

struct internalNode* root = NULL;

root=createTree(myVectorX,myVectorY,root,0);
//cout<<searchMyPoint(root,{4,30,8});
printLevelOrder(root);
cout<< "asdasd"<<searchMyPoint(root,{28287,373,357});
cout<< "asdasd"<<searchMyPoint(root,{28282,373,357});
/*
root = insertIntoKD(root,{1,1,1});
root = insertIntoKD(root,{2,2,5});
root = insertIntoKD(root,{3,3,3});
printLevelOrderWithLeaves(root);
root = insertIntoKD(root,{4,4,5});
root = insertIntoKD(root,{5,5,1});
root = insertIntoKD(root,{6,7,6});
cout<<endl<<"asdasdasd";
printLevelOrderWithLeaves(root);
cout<<"asdasd"<<endl;
cout<< searchMyPoint(root,{3,3,3});

//bool pointInside(internalNode* root,vector<int>point, vector<int>regionPoint1, vector<int>regionPoint2){

//cout<<searchMyPoint(root,{5,19,123});
*/
}
