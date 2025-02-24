#version 330


//頂点属性を指定する
in vec3 inPosition;
void main()
{

	//行列計算のためにw成分を追加する
	gl_Position = vec4(inPosition, 1.0);
}