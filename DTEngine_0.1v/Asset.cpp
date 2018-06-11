#include "pch.h"
#include "Asset.h"


template <typename T>
Asset::Asset()
{
}

Asset::~Asset()
{
}

void Asset::Initialize()
{

}

void Asset::Dispose()
{
	for (auto iter : textures_)
		delete iter.second;
}

void Asset::Ready(string root_file_path)
{
	for (auto iter : textures_)
		delete iter.second;

	files_to_load_ = 0;
	paths_.clear();

	for (recursive_directory_iterator iter(root_file_path); iter != recursive_directory_iterator(); iter++) {
		string extension = iter->path().extension().string();
		if (extension == ".png" || extension == ".dds") {
			wstring wstr;
			wstr.assign(iter->path().string().begin(), iter->path().string().end());
			paths_.push_back(wstr);
		}
	}

	files_to_load_ = paths_.size();
	pathIter_ = paths_.begin();
}

void Asset::LoadNext()
{
	GetTexture(pathIter_->data());
	pathIter_++;
}

Texture* Asset::GetTexture(wstring p)
{
	if (!exists(p))
		cout << "파일 없음 : " << p << endl;

	if (!textures_[p]) {
		textures_[p] = new Texture();
		//D3DX11CreateShaderResourceViewFromFile(, p.data(), &textures_[p]->info_, NULL, &textures_[p]->texture_, NULL);

		files_loaded_++;
	}

	return textures_[p];
}