#include"VertexArray.h"

/*************************************************/
/*関数名 : VertexArray                           */
/*戻り値 : 無し                                  */
/*引数   : verts(頂点バッファ)                   */
/*引数   : numVerts(頂点の数)                    */
/*引数   : indices(インデックスバッファ)         */
/*引数   : numIndices(インデックスの数)          */
/*処理   : 頂点,インデックス情報の初期化         */
/*備考   : 無し                                  */
/*************************************************/
VertexArray::VertexArray(const F32* verts, U16 numVerts, const U16* indices, U16 numIndices)
	:mNumIndices(numIndices),
	mNumVerts(numVerts)
{
	/*勉強用：頂点配列.頂点バッファ,インデックスバッファの違い  　          　　                           */
	/*      ：頂点配列                 → 頂点情報を配列に格納しておき、描画時にCPUからGPUに向けて転送する */
	/*      ：頂点バッファ             → 頂点情報を格納するメモリバッファ　　　　　                       */
	/*      ：インデックスバッファ     → インデックス情報を格納するメモリバッファ　                       */
	
	
	//頂点配列オブジェクトを作成してバインド(使用の指定)する
	/* 勉強用：glGenVertexArraysの第1引数は頂点配列オブジェクトの数 */
    glGenVertexArrays(1, &mVertexArrayID);
	/* 勉強用：glBindVertexArrayの引数で指定されたオブジェクト名の頂点配列オブジェクトを結合する */
	glBindVertexArray(mVertexArrayID);

	//同様に頂点バッファを作成してバインドする
	glGenBuffers(1,&mVertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER,mVertexBufferID);
	glBufferData(
		GL_ARRAY_BUFFER,                          //バッファの種類
		numVerts * TOTAL_VERTS_NUM * sizeof(F32), //確保するバイト数
		verts,                                    //コピー元
		GL_STATIC_DRAW                            //データの利用方法
	);

	//同様にインデックスバッファを作成してバインドする
	glGenBuffers(1, &mIndexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferID);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,                  //バッファの種類
		numIndices * sizeof(U32),                 //確保するバイト数
		indices,                                  //コピー元
		GL_STATIC_DRAW                            //データの利用方法
	);

	glEnableVertexAttribArray(0);
	/* 勉強用：レンダリング時に index に指定された位置にある attribute 変数が受け取るデータの場所と書式を指定する  */
	/* 勉強用：色々と何のこっちゃになっているので整理
	         : attributeとはデータの塊(イメージはTLSとかのペイロード)
			 : データ例 ： | attribute0 | attribute1 | attribute2 | attribute0 | attribute1 | attribute2 |…
			 :上記のようにデータの塊になっているため第1引数ではその使いたい"attribute"の番号を指定する
			 :第4引数の要素間の間隔とはつまりattributeの長さになる
			 :"attribute0"にxyz座標を指定しているので"attribute1"までの長さはfloatのデータサイズ*座標数になる
			 :オフセットは指定した"attribute"が先頭からどれだけ離れているかになる
			 :"attribute1"を第1引数に指定するならばオフセットは"attribute0"分のsizeof(F32)* COODINATE_NUMになる(※ポインター型なので注意)	
	*/
	//attribute0はxyz座標を記憶する
	glVertexAttribPointer(
		COODINATE_ATRIBUTE_POS,     //attribute変数の位置
		COODINATE_NUM,              //データサイズ
		GL_FLOAT,                   //データの型
		GL_FALSE,                   //正規化の有無
		sizeof(F32)* COODINATE_NUM, //要素間の間隔
		0                           //オフセット
	);
	glEnableVertexAttribArray(1);


}

/*************************************************/
/*関数名 : ~VertexArray                          */
/*戻り値 : 無し                                  */
/*引数   : なし                                  */
/*処理   : 頂点,インデックス情報の削除           */
/*備考   : 無し                                  */
/*************************************************/
VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBufferID);
	glDeleteBuffers(1, &mIndexBufferID);
	glDeleteVertexArrays(1, &mVertexArrayID);
}

/*************************************************/
/*関数名 : SetVertexActive                       */
/*戻り値 : 無し                                  */
/*引数   : なし                                  */
/*処理   : 頂点配列の有効化                      */
/*備考   : 無し                                  */
/*************************************************/
void VertexArray::SetVertexActive()
{
	glBindVertexArray(mVertexArrayID);
}