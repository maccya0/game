#version 330


//���_�������w�肷��
in vec3 inPosition;
void main()
{

	//�s��v�Z�̂��߂�w������ǉ�����
	gl_Position = vec4(inPosition, 1.0);
}