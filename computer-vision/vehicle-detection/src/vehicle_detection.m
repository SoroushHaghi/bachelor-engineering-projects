clc;
close all; 
clear all;

for numi=1:4
    name=[num2str(numi), '.webm'];
    vr=VideoReader(name);
    %detect day or night
    framedn=read(vr,3);
    g=rgb2hsv(framedn);
    v=g(:,:,3);
    % figure;imhist(v);title('histogram');
    hist=imhist(v);
    [xhist,yhist]=size(hist);
    di=0;
    maximum=max(hist(:));
    for i=1:xhist
        if hist(i,1)==maximum
            di=i;
        end
    end

    night=0;
    if (1<=di)&&(di<=30)
        night=1;
    end   
    
    %for day time
    if night==0
        error=0;
        ec=0;
        videoReader = vision.VideoFileReader(name);
        info = mmfileinfo(name);
        d=info.Duration;
        f=5;
        e=f+1;
        foregroundDetector = vision.ForegroundDetector('NumGaussians', 3,'NumTrainingFrames', f);
        for z=e:5:d
            %detect foreground
            for i=1:150
                frame = step(videoReader);
                foreground = step(foregroundDetector, frame);
            end
    
            %show frame of video
            figure;subplot(3,2,1); imshow(frame); title(['videonum:',num2str(numi),'   ,frame']);
            %show foreground
            subplot(3,2,2); imshow(foreground); title('Foreground');
    
            %delete unexpected object after detect foreground
            se1 = strel('disk', 2);
            foregroundclose = imclose(foreground, se1);
            fillholes=imfill(foregroundclose,'holes');
            se2 = strel('disk', 5);
            pic = imopen(fillholes, se2);

            subplot(3,2,3); imshow(pic); title('delete unexpected object ');

            [x,y]=size(pic);
            m=(x/2)+1;
            [p,n]=bwlabel(pic);
            area=regionprops(p,'Area');
            bb = regionprops(p,'BoundingBox');
            for i=1:n
                bbarea(i,1) = (bb(i).BoundingBox(3))*(bb(i).BoundingBox(4));
                k=area(i).Area;
                r = k/ bbarea(i,1);
                if r > 0.4
                    d(i,1)=1;
                else 
                    d(i,1)=0;
                end
            end
            c=0;
            s = regionprops(p,'centroid');
            centroids = cat(1, s.Centroid);
    
            subplot(3,2,4);imshow(frame); title('Detected Cars');
            hold on
            for i=1:n
                rectangle('Position',bb(i).BoundingBox,'EdgeColor','b','LineWidth',3);
            end
            hold off

            subplot(3,2,[5,6]);imshow(frame)
            hold on
            rectangle('Position',[(0+1),m,(y-1),(m-3)],'EdgeColor','b','LineWidth',3)
            hold off
            hold on
            for i=1:n
                if d(i,1)== 1 && (centroids(i,2)>m)
                    rectangle('Position',bb(i).BoundingBox,'EdgeColor','r','LineWidth',2)
                    c=c+1;
                end
            end
            if c==0;
                ec=ec+1;
            end
            hold off
            if ec==4;
                break;
            end
        end
    end

    %for night time
    if night==1
        error=0;
        ec=0;
        info = mmfileinfo(name);
        d=info.Duration;
        for i=1:5:d
            frame=read(vr,i);
    
            figure;subplot(2,2,1);imshow(frame);title(['videonum:',num2str(numi),'   ,frame']);

            f2bw=im2bw(frame);
            subplot(2,2,2);imshow(f2bw); title('bw');

            se=strel('disk',1);
            opening=imopen(f2bw,se);
            subplot(2,2,3);imshow(opening); title('opening');

            [x,y]=size(opening);
            f=(x/2)+1;
            [a,n]=bwlabel(opening);
            s = regionprops(a,'centroid');
            b = regionprops(a,'BoundingBox');
            centroids = cat(1, s.Centroid);
            e=0;
            c=0;
            for j=1:n
                if f<centroids(j,2)
                     e=e+1;
                end
                c=round(e/2);
            end
            if c==0;
                ec=ec+1;
            end
            if ec==4;
                break;
            end
    
            subplot(2,2,4);imshow(frame); title(['number of car :',num2str(c)]);
            hold on
            rectangle('Position',[(0+1),f,(y-1),(f-3)],'EdgeColor','b','LineWidth',3)
            hold off
            hold on 
            for j=1:n
                if f<centroids(j,2)
                    rectangle('Position',b(j).BoundingBox,'EdgeColor','red','LineWidth',2)
                end
            end
            hold off
        end
    end 
end
