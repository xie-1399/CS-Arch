'''
(1)Help to deal the picture of MD file
(2)Convert the MDfile to the PDF using pandoc
:eg :wq

Usage:
python3 misc.py --file ./OpenSBI.md --topic OpenSBI  //get picture and rewrite
'''
import argparse
import os
import re

counter = 1
id = 1
def rename(type,text):
    global counter
    if(str(text).find(type) !=-1):
        name = args.topic + str(counter) + ".png"
        regex = re.sub(r'\b\w+\.png\b',name,text)
        counter += 1
        return regex
def mkdir(filename):
    command = "mkdir " + filename
    try:
        os.system(command)
    except:
        raise Exception("Can't mkdir")

def get_picture(file,topic,picpath = "/home/xxl/RISCVZone/doc/pic"):
    global id
    filepath = "/mnt/c"
    file = file.split('\\')
    type = str(file[-1]).replace("\n","").endswith(".png")
    for string in file[1:]:
        if string.find(" ") != -1:
            string_tmp =""
            tmp_string = string.split(" ")
            for ts in tmp_string[0:-1]:
                string_tmp += ts + "\\" + ' '
            string = string_tmp + tmp_string[-1]
        filepath += "/" + string
    if(type):
        command = "sudo " + "cp -r " + filepath + " " + picpath + "/" + str(topic) \
                   + "/" + str(topic) + str(id) + ".png"
        print(command)
    else:
        command = "sudo " + "cp -r " + filepath + " " + picpath + "/" + str(topic) \
                  + "/" + str(topic) + str(id) + ".jpg"
    id += 1
    try:
        os.system(command)
    except:
        raise Exception("Not get picture")


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description="Markdown Misc")
    parser.add_argument("--rename",required=False,
                        help="Rename the picture of MDfile")
    parser.add_argument("--update",required=False,
                        help="Update the name of picture")

    #just command has then True
    parser.add_argument("--convert",required=False,action="store_true")

    parser.add_argument("--file",required=True,type=str)

    parser.add_argument("--topic",type=str)

    args = parser.parse_args()

    #Maybe need clash
    if(args.convert):
        print("Convert {file}...".format(
            file = str(args.file).split('/')[-1]))
        pdffile = str(args.file).split('/')[-1] + '.pdf'
        command = "pandoc {mdfile} -s -o {pdffile}".format(
            mdfile = args.file,pdffile = pdffile
        )
        try:
            os.system(command)
        except:
            raise Exception("Convert Fail!")

    else:
        print("update the MD File!")
        dir_path = "./pic/" + args.topic
        if(not os.path.exists(dir_path)):
            mkdir(dir_path)

        with open(args.file,"r+") as mdfile:
            md_text = mdfile.readlines()
            update_list = []
            for text in md_text:
                if(str(text).find(".png") !=-1):
                    pic_path = text.split('(')[-1].replace(")","").replace("\n","")
                    print("pic_path:",pic_path)
                    get_picture(pic_path,args.topic)
                    text = rename("png",text)
                    text = "https://github.com/xie-1399/RISCVZone/tree/main/doc/pic/"+ args.topic + "/" \
                           + text.split("\\")[-1].replace(")","")
                elif(str(text).find(".jpg")!=-1):
                    pic_path = text.split('(')[-1].replace(")","").replace("\n","")
                    get_picture(pic_path,args.topic)
                    text = rename("jpg",text)
                    text = "https://github.com/xie-1399/RISCVZone/tree/main/doc/pic/"+ args.topic + "/" \
                           + text.split("\\")[-1].replace(")","")
                update_list.append(text)

        #Update file
        with open(args.file,"w+") as update:
            for update_data in update_list:
                update.write(update_data)
