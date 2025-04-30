import face_recognition
import cv2
import os

# 定义一个函数来加载和编码人脸
def load_and_encode_faces(directory):
    known_face_encodings = []
    known_face_names = []
    for filename in os.listdir(directory):
        if filename.endswith(".jpg") or filename.endswith(".png"):
            image = face_recognition.load_image_file(os.path.join(directory, filename))
            face_encoding = face_recognition.face_encodings(image)[0]
            known_face_encodings.append(face_encoding)
            known_face_names.append(os.path.splitext(filename)[0])
    return known_face_encodings, known_face_names

# 加载已知人脸
known_face_encodings, known_face_names = load_and_encode_faces("known_faces")

# 加载未知图片
unknown_image = face_recognition.load_image_file("unknown.jpg")
unknown_face_locations = face_recognition.face_locations(unknown_image, model="hog")
unknown_face_encodings = face_recognition.face_encodings(unknown_image, unknown_face_locations)

# 在图片上绘制人脸矩形框和标签
for (top, right, bottom, left), face_encoding in zip(unknown_face_locations, unknown_face_encodings):
    # 比较人脸
    matches = face_recognition.compare_faces(known_face_encodings, face_encoding)
    name = "Unknown"

    # 找到最匹配的人脸
    face_distances = face_recognition.face_distance(known_face_encodings, face_encoding)
    best_match_index = face_distances.argmin()
    if matches[best_match_index]:
        name = known_face_names[best_match_index]

    # 绘制矩形框
    cv2.rectangle(unknown_image, (left, top), (right, bottom), (0, 255, 0), 2)
    # 绘制标签
    cv2.putText(unknown_image, name, (left, top - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0, 255, 0), 2)

# 显示图片
cv2.imshow("Unknown Image", unknown_image)
cv2.waitKey(0)
cv2.destroyAllWindows()