#include "Shader.h"
#include <fstream>
#include <sstream>
/*************************************************/
/*関数名 : LoadShader                            */
/*戻り値 : 無し                                  */
/*引数   : vertName(頂点シェーダー名)            */
/*引数   : flagName(フラグメントシェーダー名)    */
/*処理   : シェーダーのロード                    */
/*備考   : 無し                                  */
/*************************************************/
bool Shader::LoadShader(const std::string& vertName, const std::string& flagName)
{
	if ((!CompileShader(vertName, GL_VERTEX_SHADER, mVertexShaderID)) ||
		(!CompileShader(flagName, GL_FRAGMENT_SHADER, mFragShaderID)))
	{
		return false;
	}


	//頂点/フラグメントシェーダーをリンクしてシェーダープログラムを作成する
	mShaderProgramID = glCreateProgram();
	glAttachShader(mShaderProgramID, mVertexShaderID);
	glAttachShader(mShaderProgramID, mFragShaderID);
	glLinkProgram(mShaderProgramID);

	if (!IsValidProgram())
	{
		return false;
	}

	return true;
}

/*************************************************/
/*関数名 : UnloadShader                          */
/*戻り値 : 無し                                  */
/*引数   : なし                                  */
/*処理   : シェーダーのアンロード                */
/*備考   : 無し                                  */
/*************************************************/
void Shader::UnloadShader()
{
	//プログラム→シェーダーの順で削除する
	glDeleteProgram(mShaderProgramID);
	glDeleteShader(mVertexShaderID);
	glDeleteShader(mFragShaderID);
}

/*************************************************/
/*関数名 : CompileShader                         */
/*戻り値 : 無し                                  */
/*引数   : fileName(シェーダーのファイル名)      */
/*引数   : shaderType(シェーダーの種類)          */
/*引数   : outShader(シェーダーのコンパイル結果) */
/*処理   : シェーダーのコンパイル                */
/*備考   : 無し                                  */
/*************************************************/
bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
	std::ifstream shaderFile(fileName);

	if (shaderFile.is_open())
	{
		std::stringstream sstream;

		//全テキストを1つの文字列として読み出す
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();

		//指定されたシェーダータイプのシェーダーを作成
		/* 勉強用：シェーダータイプは以下の種類がある                                                                 　　　　*/
		/* GL_VERTEX_SHADER    : 頂点が持っている情報を演算する                                                       　　　　*/
		/* GL_FRAGMENT_SHADER  : 各ピクセルの色の演算を行う                                                          　　　　 */
		/* GL_GEOMETRY_SHADER  : プリミティブごとの処理を行い，かつ，新しいプリミティブを作り出すことができるシェーダ　　　　 */
		/* →ざっくりいうとバーテックスシェーダーとフラグメントシェーダーだけだと材質表現できないから中間のシェーダーを用いる */
		outShader = glCreateShader(shaderType);
		
		//コンパイルの実行
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);

		if (!IsCompiled(outShader))
		{
			SDL_Log("Failed to compile shader %s", fileName.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("Shader file not found: %s", fileName.c_str());
		return false;
	}
	return true;
}

/*************************************************/
/*関数名 : IsCompiled                            */
/*戻り値 : 無し                                  */
/*引数   : shader(シェーダーID)                  */
/*処理   : シェーダーのコンパイル完了確認        */
/*備考   : 無し                                  */
/*************************************************/
bool Shader::IsCompiled(GLuint shader)
{
	GLint status;

	//コンパイルの有無を問い合わせる
	glGetShaderiv(shader,GL_COMPILE_STATUS,&status);

	if (status != GL_TRUE)
	{
		//コンパイルエラーの原因を出力する
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}
	return true;
}

/*************************************************/
/*関数名 : SetShaderActive                       */
/*戻り値 : 無し                                  */
/*引数   : なし　　　　　　　　                  */
/*処理   : シェーダープログラムの有効化          */
/*備考   : 無し                                  */
/*************************************************/
void Shader::SetShaderActive()
{
	glUseProgram(mShaderProgramID);
}


/*************************************************/
/*関数名 : IsValidProgram                        */
/*戻り値 : 無し                                  */
/*引数   : なし　　　　　　　　                  */
/*処理   : リンクの完了確認　　　　　　　        */
/*備考   : 無し                                  */
/*************************************************/
bool Shader::IsValidProgram()
{
	GLint status;

	//リンクの有無を問い合わせる
	glGetProgramiv(mShaderProgramID, GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		//コンパイルエラーの原因を出力する
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(mShaderProgramID, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}
	return true;
}
