#pragma once

#include <opencv2/opencv.hpp>
#include <onnxruntime_cxx_api.h>

struct Configuration
{
	float SegThreshold; // Segmentation Confidence Threshold(�ָ���ֵ)
	bool UseSingleMask;
	bool UseBoxInfo;
	std::string EncoderModelPath;
	std::string DecoderModelPath;
	std::string SaveDir;
	std::string Device;
	
};

typedef struct BoxInfo 
{
	int x1; // (x1,y1)Ϊ��ѡ�������Ͻǽǵ�
	int y1;
	int x2; // (x2,y2)Ϊ��ѡ�������½ǽǵ�
	int y2;
}BoxInfo;


struct ClickInfo
{
	cv::Point pt;
	bool positive;
};

class SAMOnnxRunner 
{
private:
	// Encoder Settings Params
	bool InitEncoder;
	int EncoderInputSize = 1024;

	// Decoder Settings Params
	float SegThreshold;

	// Env Settings Params
	std::string device{ "cpu" };
	Ort::Env env;
	Ort::SessionOptions session_options;
	Ort::Session *EncoderSession = nullptr;
	Ort::Session *DecoderSession = nullptr;

	// CPU MemoryInfo and memory allocation
	Ort::AllocatorWithDefaultOptions allocator;
	Ort::MemoryInfo memory_info_handler = Ort::MemoryInfo::CreateCpu(
		OrtArenaAllocator, OrtMemTypeDefault
	);

	// Hardcode input node names
	// Encoder
	unsigned int encoder_num_inputs = 1;
	std::vector<const char*> encoder_input_node_names;
	std::vector<std::vector<int64_t>> encoder_input_node_dims;
	// Decoder
	unsigned int decoder_num_inputs = 2;
	std::vector<const char*> decoder_input_node_names;
	std::vector<std::vector<int64_t>> decoder_input_node_dims;

	// Hardcode output node names
	// Encoder
	unsigned int encoder_num_outputs = 1;
	std::vector<const char*> encoder_output_node_names;
	std::vector<std::vector<int64_t>> encoder_output_node_dims;
	// Decoder
	unsigned int decoder_num_outputs = 1;
	std::vector<const char*> decoder_output_node_names;
	std::vector<std::vector<int64_t>> decoder_output_node_dims;
	
	// input value handlers
	std::vector<float> input_bgr_value_handler;

	/* 2023.05.05
	* TODO : ��װ��һ������
	*/

protected:
	const unsigned int num_threads;

	cv::Mat Image_PreProcess(cv::Mat srcImage);
	Ort::Value Encoder_PreProcess(cv::Mat Image);
	void Decoder_PreProcess();

	void Encoder_BuildEmbedding();
	void Decoder_Inference();

	void Encoder_PostProcess();
	void Decoder_PostProcess();



public:
	explicit SAMOnnxRunner(unsigned int num_threads = 1);
	~SAMOnnxRunner();

	void InitOrtEnv(Configuration cfg);

	void InferenceSingleImage(Configuration cfg, cv::Mat srcImage, ClickInfo clickInfo);

	void setSegThreshold(float threshold);

	void ResetInitEncoder();

};