#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <time.h>
#include<cmath>

using namespace std;

void calculateNormals(vector<vector<string>> &vertices, vector<vector<string>> &faces, vector<vector<float>> &normals){
    vector<float> vectorA;
    vector<float> vectorB;
    vector<float> vectorC;
    vector<float> edgeVector1;
    vector<float> edgeVector2;
    vector<float> normalVector;
    for (int faceI = 0; faceI < faces.size(); faceI++) {

        vectorA.push_back(stof(vertices[stoi(faces[faceI][0])-1][0]));
        vectorA.push_back(stof(vertices[stoi(faces[faceI][0])-1][1]));
        vectorA.push_back(stof(vertices[stoi(faces[faceI][0])-1][2]));

        vectorB.push_back(stof(vertices[stoi(faces[faceI][1])-1][0]));
        vectorB.push_back(stof(vertices[stoi(faces[faceI][1])-1][1]));
        vectorB.push_back(stof(vertices[stoi(faces[faceI][1])-1][2]));

        vectorC.push_back(stof(vertices[stoi(faces[faceI][2])-1][0]));
        vectorC.push_back(stof(vertices[stoi(faces[faceI][2])-1][1]));
        vectorC.push_back(stof(vertices[stoi(faces[faceI][2])-1][2]));

        edgeVector1.push_back(vectorB[0]-vectorA[0]);
        edgeVector1.push_back(vectorB[1]-vectorA[1]);
        edgeVector1.push_back(vectorB[2]-vectorA[2]);

        edgeVector2.push_back(vectorC[0]-vectorA[0]);
        edgeVector2.push_back(vectorC[1]-vectorA[1]);
        edgeVector2.push_back(vectorC[2]-vectorA[2]);
//        for (int i=0;i<3;i++){
//            vectorA.push_back(stof(vertices[stoi(faces[faceI][i])-1][i]));
//            vectorB.push_back(stof(vertices[stoi(faces[faceI][i])-1][i]));
//            vectorC.push_back(stof(vertices[stoi(faces[faceI][i])-1][i]));
//        }
//
//        for (int i=0;i<3;i++){
//            edgeVector1.push_back(vectorB[i]-vectorA[i]);
//            edgeVector2.push_back(vectorC[i]-vectorA[i]);
//
//        }
        float normalVecMag;
        normalVector.push_back((edgeVector1[1]*edgeVector2[2])-(edgeVector1[2]*edgeVector2[1]));
        normalVector.push_back((edgeVector1[2]*edgeVector2[0])-(edgeVector1[0]*edgeVector2[2]));
        normalVector.push_back((edgeVector1[0]*edgeVector2[1])-(edgeVector1[1]*edgeVector2[0]));
        normalVecMag = sqrt(pow(normalVector[0],2)+pow(normalVector[1],2) + pow(normalVector[2],2));
        normalVector[0]= normalVector[0]/normalVecMag;
        normalVector[1]= normalVector[1]/normalVecMag;
        normalVector[2]= normalVector[2]/normalVecMag;
        normals.push_back(normalVector);

        vectorA.clear();
        vectorB.clear();
        vectorC.clear();
        edgeVector1.clear();
        edgeVector2.clear();
        normalVector.clear();
    }
}

void averageNormals(vector<vector<string>> &vertices, vector<vector<string>> &faces, vector<vector<float>> &normals, vector<vector<float>> &averagedNormals){
    vector<float> indAverageNormal;
    for (int vertexNumber=1; vertexNumber<vertices.size()+1;vertexNumber++){
        indAverageNormal.push_back(0.0);
        indAverageNormal.push_back(0.0);
        indAverageNormal.push_back(0.0);
        int vertexCount = 0;
        for (int faceNumber=0; faceNumber<faces.size(); faceNumber++){
            if( stoi(faces[faceNumber][0]) == vertexNumber || stoi(faces[faceNumber][1])==vertexNumber || stoi(faces[faceNumber][2])==vertexNumber){
//                cout<<"Found"<<endl;
                vertexCount++;
                indAverageNormal[0] = indAverageNormal[0] + normals[faceNumber][0];
                indAverageNormal[1] = indAverageNormal[1] + normals[faceNumber][1];
                indAverageNormal[2] = indAverageNormal[2] + normals[faceNumber][2];
            }
        }
        indAverageNormal[0] = indAverageNormal[0]/vertexCount;
        indAverageNormal[1] = indAverageNormal[0]/vertexCount;
        indAverageNormal[2] = indAverageNormal[0]/vertexCount;
        averagedNormals.push_back(indAverageNormal);
        indAverageNormal.clear();
    }
}

void gaussNoise(vector<vector<string>> &vertices, vector<vector<float>> &averagedNormals){
    float rho = 0.3;
    srand (time(NULL));
    int prob;
    for (int vertexNumber=0; vertexNumber<vertices.size(); vertexNumber++){
        prob = rand() % 10 + 1;
        if (prob%2==0){
            vertices[vertexNumber][0] = to_string(stof(vertices[vertexNumber][0])+rho*averagedNormals[vertexNumber][0]);
            vertices[vertexNumber][1] = to_string(stof(vertices[vertexNumber][1])+rho*averagedNormals[vertexNumber][1]);
            vertices[vertexNumber][2] = to_string(stof(vertices[vertexNumber][2])+rho*averagedNormals[vertexNumber][2]);
        }
    }
}


int main(){
    ifstream MyReadFile("teapot.obj");
    string myText;
    vector<vector<string>> vertices;
    vector<vector<string>> faces;
    vector<vector<float>> normals;
    vector<vector<float>> averagedNormals;
    vector<string> line;

    while (getline (MyReadFile, myText)) {
        if(myText[0]=='v' && myText[1]==' '){
            std::istringstream iss(myText);
            for(string myText; iss >> myText; )
            line.push_back(myText);
            line.erase(line.begin());
            vertices.push_back(line);
            line.clear();
        }
        else if(myText[0]=='f' && myText[1]==' '){
            std::istringstream iss(myText);
            for(string myText; iss >> myText; )
            line.push_back(myText);
            line.erase(line.begin());
            faces.push_back(line);
            line.clear();
        }
    }
    calculateNormals(vertices,faces,normals);
    averageNormals(vertices,faces,normals,averagedNormals);
    gaussNoise(vertices,averagedNormals);

//  Display
//    cout<<"start"<<endl;
//    for (int i = 0; i < normals.size(); i++) {
//        for (int j = 0; j < normals[i].size(); j++)
//            cout << normals[i][j] << " ";
//        cout << endl;
//    }

    ofstream MyFile("noisy_teapot.obj");
    for (int vertexNumber=0; vertexNumber<vertices.size();vertexNumber++){
        MyFile << "v "<<vertices[vertexNumber][0]<<" "<<vertices[vertexNumber][1]<<" "<<vertices[vertexNumber][2] <<"\n";
    }
    for (int faceNumber=0; faceNumber<faces.size();faceNumber++){
        MyFile << "f "<<faces[faceNumber][0]<<" "<<faces[faceNumber][1]<<" "<<faces[faceNumber][2] <<"\n";
    }

}

