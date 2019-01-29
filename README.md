# HIGHLIGHT MAKER
##  소개
> 시청자의 표정 인식을 통해 영상 종료 후 
> 자동으로 하이라이트 영상을 제작해주는 어플리케이션

  기존의 하이라이트 영상은 제작자가 생각하기에 중요하다고 생각하는 부분을 편집하여 만들어졌다. 하지만 기존 방식은 2가지의 문제를 가지고 있다. 첫째, 시청자의 관점이 반영되지않아 공감을 얻기 어려운 경우가 많다. 둘째, 영상 시청후 별도의 시간을 들여 편집해야한다.
HIGHLIGHT MAKER를 통해 시청자의 표정을 인식하여 로그를 생성하고 이를 기반으로 자동으로 하이라이트 영상을 제작할수있다! 

## 요구사항
* IDE for c++
* opencv 3.2.0 for smile detection
* ffmpeg for editting video

## 미소 인식
>opencv cascade classifier를 사용하여 얼굴을 찾고 그 안에서 미소를 인식했다.

 1. 얼굴 인식
   > 얼굴 전체를 인식한다
  ![](https://github.com/pouder-Man/Highlight_Maker/blob/master/image/00_faceDetection.png)
  
 2. 하관 인식
    > 얼굴 전체의 범위에서 미소를 인식할 경우 눈, 광대등의 위치에서 미소를 오검출하는 경우가 있어  하관을 인식

  ![](https://github.com/pouder-Man/Highlight_Maker/blob/master/image/01_faceDetection.png)
 
 3. 미소 인식
    > 하관의 범위내에서 미소를 인식한다. 미소가 인식될 경우 로그를 기록한다.

  ![](https://github.com/pouder-Man/Highlight_Maker/blob/master/image/02_smileDetection.png)

## 동영상 편집
> 미소 인식 로그를 기반으로 ffmpeg을 사용하여 동여상을 편집한다.
 1. 영상 재생
 
  ![](https://github.com/pouder-Man/Highlight_Maker/blob/master/image/04_videoPlayProcess.png)
 
 2. 영상 편집
 
  ![](https://github.com/pouder-Man/Highlight_Maker/blob/master/image/05_videoEditProcess.png)


## usecase diagram
  
  ![](https://github.com/pouder-Man/Highlight_Maker/blob/master/image/06_usecaseDiagram.png)

## class diagram
  
  ![](https://github.com/pouder-Man/Highlight_Maker/blob/master/image/07_classDiagram.png)

## 결과
  ![](https://github.com/pouder-Man/Highlight_Maker/blob/master/image/08_result01.png)
  ![](https://github.com/pouder-Man/Highlight_Maker/blob/master/image/09_result02.png)
  ![](https://github.com/pouder-Man/Highlight_Maker/blob/master/image/10_result03.png)
