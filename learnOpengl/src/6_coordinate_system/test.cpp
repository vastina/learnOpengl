#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <Windows.h>

using namespace std;
using namespace glm;
/*它的矩阵是写出来的转置
比如glm::mat2（
0.0 1.0
0.0 0.0)
其实是
[ 0.0 0.0
  1.0 0.0 ]
不是很懂。。。
*/
void print(const mat4 &m) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			cout << m[j][i] << " ";
		cout << "\n";
	}
	cout << "\n";
}

int main() {
	int time = clock();
	while (true) {
		float t = (float)(clock() - time) / 1000.0;
		glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		print(transform);
		transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		print(transform);
		 transform = glm::rotate(transform, t, glm::vec3(0.0f, 0.0f, 1.0f));
		print(transform);
		system("pause");
	}
}