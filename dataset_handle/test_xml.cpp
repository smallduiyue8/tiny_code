#include "tinyxml.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

string int_to_string(int input_int){
	ostringstream stream;
	stream << input_int;
	return stream.str();
}

string int_to_6_string(int input_int){
	ostringstream ss;
    ss << setfill('0') << setw(6) << input_int << endl;
    return ss.str();
}

struct bbox{
    int xmin;
    int ymin;
    int xmax;
    int ymax;
};

enum SuccessEnum {FAILURE, SUCCESS};

SuccessEnum saveXML(string pic_name, string pic_path, string pic_type, bbox target)
{
    TiXmlDocument doc;

    TiXmlElement* annotation = new TiXmlElement("annotation");
    doc.LinkEndChild(annotation);

    TiXmlElement* folder = new TiXmlElement("folder");
    annotation -> LinkEndChild(folder);
    TiXmlText* folder_text = new TiXmlText("turtlebot");  ///文本
    folder -> LinkEndChild(folder_text);
    
    TiXmlElement* filename = new TiXmlElement("filename");
    annotation -> LinkEndChild(filename);
    TiXmlText* filename_text = new TiXmlText(pic_name);  ///文本
    filename -> LinkEndChild(filename_text);

    TiXmlElement* path = new TiXmlElement("path");
    annotation -> LinkEndChild(path);
    TiXmlText* path_text = new TiXmlText(pic_path);  ///文本
    path -> LinkEndChild(path_text);

    TiXmlElement* source = new TiXmlElement("source");
    annotation -> LinkEndChild(source);

    {
        TiXmlElement* database = new TiXmlElement("database");
        source -> LinkEndChild(database);
        TiXmlText* database_text = new TiXmlText("turtlebot dataset made by WYZ");  ///文本
        database -> LinkEndChild(database_text);
    }

    TiXmlElement* size = new TiXmlElement("size");
    annotation -> LinkEndChild(size);

    {
        TiXmlElement* width = new TiXmlElement("width");
        size -> LinkEndChild(width);
        TiXmlText* width_text = new TiXmlText("1920");  ///文本
        width -> LinkEndChild(width_text);

        TiXmlElement* height = new TiXmlElement("height");
        size -> LinkEndChild(height);
        TiXmlText* height_text = new TiXmlText("1080");  ///文本
        height -> LinkEndChild(height_text);

        TiXmlElement* depth = new TiXmlElement("depth");
        size -> LinkEndChild(depth);
        TiXmlText* depth_text = new TiXmlText("3");  ///文本
        depth -> LinkEndChild(depth_text);
    }

    TiXmlElement* segmented = new TiXmlElement("segmented");
    annotation -> LinkEndChild(segmented);
    TiXmlText* segmented_text = new TiXmlText("0");  ///文本
    segmented -> LinkEndChild(segmented_text);

    TiXmlElement* object = new TiXmlElement("object");
    annotation -> LinkEndChild(object);

    {
        TiXmlElement* name = new TiXmlElement("name");
        object -> LinkEndChild(name);
        TiXmlText* name_text = new TiXmlText(pic_type);  ///文本
        name -> LinkEndChild(name_text);

        TiXmlElement* pose = new TiXmlElement("pose");
        object -> LinkEndChild(pose);
        TiXmlText* pose_text = new TiXmlText("Unspecified");  ///文本
        pose -> LinkEndChild(pose_text);

        TiXmlElement* truncated = new TiXmlElement("truncated");
        object -> LinkEndChild(truncated);
        TiXmlText* truncated_text = new TiXmlText("0");  ///文本
        truncated -> LinkEndChild(truncated_text);
        
        TiXmlElement* difficult = new TiXmlElement("difficult");
        object -> LinkEndChild(difficult);
        TiXmlText* difficult_text = new TiXmlText("0");  ///文本
        difficult -> LinkEndChild(difficult_text);

        TiXmlElement* bndbox = new TiXmlElement("bndbox");
        object -> LinkEndChild(bndbox);

        {
            TiXmlElement* xmin = new TiXmlElement("xmin");
            bndbox -> LinkEndChild(xmin);
            TiXmlText* xmin_text = new TiXmlText(int_to_string(target.xmin));  ///文本
            xmin -> LinkEndChild(xmin_text);

            TiXmlElement* ymin = new TiXmlElement("ymin");
            bndbox -> LinkEndChild(ymin);
            TiXmlText* ymin_text = new TiXmlText(int_to_string(target.ymin));  ///文本
            ymin -> LinkEndChild(ymin_text);

            TiXmlElement* xmax = new TiXmlElement("xmax");
            bndbox -> LinkEndChild(xmax);
            TiXmlText* xmax_text = new TiXmlText(int_to_string(target.xmax));  ///文本
            xmax -> LinkEndChild(xmax_text);
            
            TiXmlElement* ymax = new TiXmlElement("ymax");
            bndbox -> LinkEndChild(ymax);
            TiXmlText* ymax_text = new TiXmlText(int_to_string(target.ymax));  ///文本
            ymax -> LinkEndChild(ymax_text);
        }
    }

    bool success = doc.SaveFile("b.xml");
    doc.Clear();

    if(success)
        return SUCCESS;
    else
        return FAILURE;
}

int main(int argc, char* argv[])
{
    int pic_name = 1;
    string pic_path = "das/fds";
    string pic_type = "t";
    struct bbox target = {1, 2, 3, 4}; 
    if(saveXML(int_to_6_string(pic_name), pic_path, pic_type, target) == FAILURE)
        return 1;
    return 0;
}
