#include "TextureTerrain.h"

// Function to initialize texture
bool TextureTerrain::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const wchar_t* filename, TextureType type, bool sRGB) {
    int height, width;
    D3D11_TEXTURE2D_DESC textureDesc;
    HRESULT hResult;
    unsigned int rowPitch;
    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
    bool result;
    FILE* F;
    size_t Size = 0;
    float* data = nullptr;
    memset(&srvDesc, 0, sizeof(srvDesc));
    int numOfMips = 0;
    // Load the targa image data into memory.
    switch (type) {
      case TextureTerrain::R32:
        fopen_s(&F, StringConverter::wstr2str(filename).c_str(), "rb");
        if (F == NULL)
            return false;
        fseek(F, 0, SEEK_END);
        Size = ftell(F) / sizeof(float);
        rewind(F);
        width = sqrt(Size);
        height = Size / sqrt(Size);
        data = new float[Size];
        fread_s(data, Size * sizeof(float), sizeof(float), Size, F);
        fclose(F);

        {
            size_t data_size = 0;
            int tmp_w = width, tmp_h = height;
            while (tmp_w != 0)
            {
                data_size += tmp_w * tmp_h * sizeof(float) * 2;
                numOfMips++;
                tmp_w /= 2;
                tmp_h /= 2;
            }

            float* new_data = new float[data_size / sizeof(float)];
            memset(new_data, 0, data_size);

            tmp_w = width;
            tmp_h = height;
            size_t offset = 0;
            size_t prev_offset = 0;
            // fill first mip
            for (int i = 0; i < tmp_h; i++)
                for (int j = 0; j < tmp_w; j++)
                {
                    new_data[i * tmp_w * 2 + j * 2 + 0] = data[i * tmp_w + j]; 
                    new_data[i * tmp_w * 2 + j * 2 + 1] = data[i * tmp_w + j];
                }
            prev_offset = 0;
            offset += tmp_w * tmp_h * 2;
            tmp_w /= 2;
            tmp_h /= 2;
            
            // fill other mip
            while (tmp_w != 0)
            {
                for (int i = 0; i < tmp_h; i++)
                    for (int j = 0; j < tmp_w; j++)
                    {
                        new_data[offset + i * tmp_w * 2 + j * 2 + 0] = std::min(
                            std::min(new_data[prev_offset + (2 * i + 0) * (tmp_w * 2)* 2 + (2 * j + 0) * 2 + 0],
                                new_data[prev_offset + (2 * i + 0) * (tmp_w * 2) * 2 + (2 * j + 1) * 2 + 0]),
                            std::min(new_data[prev_offset + (2 * i + 1) * (tmp_w * 2) * 2 + (2 * j + 0) * 2 + 0],
                                new_data[prev_offset + (2 * i + 1) * (tmp_w * 2) * 2 + (2 * j + 1) * 2 + 0]));
                        new_data[offset + i * tmp_w * 2 + j * 2 + 1] = std::max(
                            std::max(new_data[prev_offset + (2 * i + 0) * (tmp_w * 2) * 2 + (2 * j + 0) * 2 + 1],
                                new_data[prev_offset + (2 * i + 0) * (tmp_w * 2) * 2 + (2 * j + 1) * 2 + 1]),
                            std::max(new_data[prev_offset + (2 * i + 1) * (tmp_w * 2) * 2 + (2 * j + 0) * 2 + 1],
                                new_data[prev_offset + (2 * i + 1) * (tmp_w * 2) * 2 + (2 * j + 1) * 2 + 1]));
                    }
                prev_offset = offset;
                offset += tmp_w * tmp_h * 2;
                tmp_w /= 2;
                tmp_h /= 2;
            }

            delete[] data;
            data = new_data;
        }

        // Setup the description of the texture.
        textureDesc.Height = height;
        textureDesc.Width = width;
        textureDesc.MipLevels = numOfMips - 1;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
        textureDesc.CPUAccessFlags = 0;
        textureDesc.MiscFlags = 0;

        // Create the empty texture.
        hResult = device->CreateTexture2D(&textureDesc, NULL, &m_texture);
        if (FAILED(hResult)) {
            delete[] data;
            return false;
        }

        // Set the row pitch of the r32g32 data.
        rowPitch = width * sizeof(float) * 2;

        // Copy the targa image data into the texture. 

        {
            int tmp_w = width, tmp_h = height;
            int mip = 0;
            float* tmp_data = data;

            while (tmp_w != 0 && mip < 10)
            {
                deviceContext->UpdateSubresource(m_texture, mip, NULL, tmp_data, rowPitch, 0);
                tmp_data += tmp_w * tmp_h * 2;
                rowPitch /= 2;
                tmp_h /= 2;
                tmp_w /= 2;
                mip++;
            }
        }
        // Setup the shader resource view description.
        srvDesc.Format = textureDesc.Format;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MostDetailedMip = 0;
        srvDesc.Texture2D.MipLevels = -1;

        // Create the shader resource view for the texture.
        hResult = device->CreateShaderResourceView(m_texture, &srvDesc, &m_textureView);
        if (FAILED(hResult)) {
            delete[] data;
            return false;
        }

        // Generate mipmaps for this texture.
        //deviceContext->GenerateMips(m_textureView);
        delete[] data;
        return true;
      case TextureTerrain::Targa:
        result = LoadTarga(filename, height, width);
        if (!result) {
            return false;
        }

        // Setup the description of the texture.
        textureDesc.Height = height;
        textureDesc.Width = width;
        textureDesc.MipLevels = 0;
        textureDesc.ArraySize = 1;
        textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        textureDesc.SampleDesc.Count = 1;
        textureDesc.SampleDesc.Quality = 0;
        textureDesc.Usage = D3D11_USAGE_DEFAULT;
        textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
        textureDesc.CPUAccessFlags = 0;
        textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

        // Create the empty texture.
        hResult = device->CreateTexture2D(&textureDesc, NULL, &m_texture);
        if (FAILED(hResult)) {
            return false;
        }

        // Set the row pitch of the targa image data.
        rowPitch = (width * 4) * sizeof(unsigned char);

        // Copy the targa image data into the texture.
        deviceContext->UpdateSubresource(m_texture, 0, NULL, m_targaData, rowPitch, 0);

        // Setup the shader resource view description.
        srvDesc.Format = textureDesc.Format;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MostDetailedMip = 0;
        srvDesc.Texture2D.MipLevels = -1;

        // Create the shader resource view for the texture.
        hResult = device->CreateShaderResourceView(m_texture, &srvDesc, &m_textureView);
        if (FAILED(hResult)) {
            return false;
        }

        // Generate mipmaps for this texture.
        deviceContext->GenerateMips(m_textureView);

        // Release the targa image data now that the image data has been loaded into the texture.
        delete[] m_targaData;
        m_targaData = nullptr;

        return true;
      case TextureTerrain::DDS:
        hResult = DirectX::CreateDDSTextureFromFileEx(device, nullptr, filename, 0,
            D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0, sRGB, nullptr, &m_textureView, 0);
 
        if (FAILED(hResult)) {
            return false;
        }

        return true;
      default:
        return true;
    }
}

// Function to realese texture
void TextureTerrain::Shutdown() {
    // Release the texture view resource.
    if (m_textureView) {
        m_textureView->Release();
        m_textureView = nullptr;
    }

    // Release the texture.
    if (m_texture) {
        m_texture->Release();
        m_texture = nullptr;
    }

    // Release the targa data.
    if (m_targaData) {
       delete[] m_targaData;
       m_targaData = nullptr;
    }
}

bool TextureTerrain::LoadTarga(const wchar_t* filename, int& height, int& width) {
    int error, bpp, imageSize, index, i, j, k;
    FILE* filePtr;
    unsigned int count;
    TargaHeader targaFileHeader;
    unsigned char* targaImage;

    // Open the targa file fo reading in binary.
    error = fopen_s(&filePtr, StringConverter::wstr2str(filename).c_str(), "rb");
    if (error != 0)
        return false;

    // Read in the file header.
    count = (unsigned int)fread(&targaFileHeader, sizeof(TargaHeader), 1, filePtr);
    if (count != 1)
        return false;

    // Get the important information from the header.
    height = (int)targaFileHeader.height;
    width = (int)targaFileHeader.width;
    bpp = (int)targaFileHeader.bpp;

    // Check that it is 32 bit and not 24 bit.
    if (bpp != 32) {
        return false;
    }

    // Calculate the size of the 32 bit image data.
    imageSize = width * height * 4;

    // Allocate memory for the targa image data.
    targaImage = new unsigned char[imageSize];
    if (!targaImage)
        return false;

    // Read in the targa image data.
    count = (unsigned int)fread(targaImage, 1, imageSize, filePtr);
    if (count != imageSize)
        return false;

    // Close the file.
    error = fclose(filePtr);
    if (error != 0)
        return false;

    // Allocate memory for the targa destination data.
    m_targaData = new unsigned char[imageSize];
    if (!m_targaData)
        return false;

    // Initialize the index into the targa destination data array.
    index = 0;

    // Initialize the index into the targa image data.
    k = (width * height * 4) - (width * 4);

    // Now copy the targa image data into the targa destination array in the correct order since the targa format is stored upside down.
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            m_targaData[index + 0] = targaImage[k + 2];  // Red.
            m_targaData[index + 1] = targaImage[k + 1];  // Green.
            m_targaData[index + 2] = targaImage[k + 0];  // Blue
            m_targaData[index + 3] = targaImage[k + 3];  // Alpha

            // Increment the indexes into the targa data.
            k += 4;
           index += 4;
        }

        // Set the targa image data index back to the preceding row at the beginning of the column since its reading it in upside down.
        k -= (width * 8);
    }

    // Release the targa image data now that it was copied into the destination array.
    delete[] targaImage;
    targaImage = 0;

    return true;
}