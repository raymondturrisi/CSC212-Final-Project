%Raymond Turrisi, CSC 212 Final Project Analysis
%sets indexing parameters for color and markers used throughout plots
clc; clear; close all;
color = [77,190,238; 119,172,48; 237,177,32; 217,83,25; 162,20,47]/255;
actualMarker = ["o","^","s","d","v"]; theoreticalMarker = "--";
sMarkerSize = 7; sLineWidth = 3;
xlabs = [];
ylabs = [];
zlabs = [];
legs = [];
axes = [];
th_plots = [];
exp_plots = [];
figs = []; k = 1;


dat = importdata("dat1.txt");
dat_r = importdata("dat1_rleaning.txt");
dat3d = importdata("dat3d.txt");
dat_3d_moving = importdata("dat_3d_moving.txt");

dat_insertions = importdata("dat_insertions.txt");
dat_searches = importdata("dat_searches.txt");
dat_blsearches = importdata("dat_balanced_searches.txt");

dat_insertions = sortrows(dat_insertions,1);
dat_searches = sortrows(dat_searches,1);
dat_blsearches = sortrows(dat_blsearches,1);

logn_t = @(n,c)(c()*log(n));



figs = [figs, figure(k)]; k = k+1;
d = polyfit(dat_insertions(:,1),dat_insertions(:,2), 4);
scatter(dat_insertions(1:2:end,1),dat_insertions(1:2:end,2), 'rx')
hold on
g = polyval(d,dat_insertions(:,1));
exp_plots = [exp_plots,plot(dat_insertions(:,1),g, 'LineWidth', 1)];
title("Insertions");
grid on
xlabs = [xlabs,xlabel("n")];ylabs = [ylabs,ylabel("Time (s)")];
axes = [axes,gca];

legs = [legs, legend('Data Points', 'Fourth order fit')]

figs = [figs, figure(k)]; k = k+1;
d = polyfit(dat_searches(:,1),dat_searches(:,2), 4);
scatter(dat_searches(1:2:end,1),dat_searches(1:2:end,2), 'rx')
hold on
g = polyval(d,dat_searches(:,1));
exp_plots = [exp_plots,plot(dat_searches(:,1),g, 'LineWidth', 1, 'Color', 'r')];
title("Searches");
grid on
xlabs = [xlabs,xlabel("n")];ylabs = [ylabs,ylabel("Time (s)")];
axes = [axes,gca];

scatter(dat_blsearches(1:2:end,1),dat_blsearches(1:2:end,2), 'bx')
hold on
g = polyval(d,dat_blsearches(:,1));
exp_plots = [exp_plots,plot(dat_blsearches(:,1),g, 'LineWidth', 1, 'Color', 'b')];
grid on
legs = [legs, legend('UB - Data Points', 'UB - Fourth order fit', 'B - Data Points', 'B - Fourth order fit')]

%plots data from left leaning tree
figs = [figs, figure(k)]; k = k+1;
scatter(dat(:,1),dat(:,2));
hold on
l = [];
for i = 1:size(dat,1)
    l = [l,plot([dat(i,1) dat(i,3)],[dat(i,2) dat(i,4)])];
    hold on
    line2arrow(l(i));
end
exp_plots = [exp_plots,l];
title("Left Leaning");
grid on
xlabs = [xlabs,xlabel("X")];ylabs = [ylabs,ylabel("Y")];
axes = [axes,gca];

%plots data from right leaning tree
figs = [figs, figure(k)]; k = k+1;
scatter(dat_r(:,1),dat_r(:,2));
hold on
l = [];
for i = 1:size(dat_r,1)
    l = [l,plot([dat_r(i,1) dat_r(i,3)],[dat_r(i,2) dat_r(i,4)])];
    hold on
    line2arrow(l(i));
end
title("Right Leaning Tree")
exp_plots = [exp_plots,l];
grid on
xlabs = [xlabs,xlabel("X")];ylabs = [ylabs,ylabel("Y")];
axes = [axes,gca];


%plots data from both left and right leaning tree
figs = [figs, figure(k)]; k = k+1;
subplot(1,2,1)
scatter(dat(:,1),dat(:,2));
hold on
l = [];
for i = 1:size(dat,1)
    l = [l,plot([dat(i,1) dat(i,3)],[dat(i,2) dat(i,4)])];
    hold on
    line2arrow(l(i));
end
title("Left Leaning Tree")
exp_plots = [exp_plots,l];
grid on
xlabs = [xlabs,xlabel("X")];ylabs = [ylabs,ylabel("Y")];
axes = [axes,gca];

subplot(1,2,2)
scatter(dat_r(:,1),dat_r(:,2));
hold on
l = [];
for i = 1:size(dat_r,1)
    l = [l,plot([dat_r(i,1) dat_r(i,3)],[dat_r(i,2) dat_r(i,4)])];
    hold on
    line2arrow(l(i));
end

title("Right Leaning Tree")
exp_plots = [exp_plots,l];
grid on
xlabs = [xlabs,xlabel("X")];ylabs = [ylabs,ylabel("Y")];
axes = [axes,gca];


%plots data from 3d tree
figure(401);
scatter3(dat3d(1:24,1),dat3d(1:24,2),dat3d(1:24,3),20,...
    'MarkerEdgeColor','k',...
    'MarkerFaceColor',[1 .6 .6]);

hold on
l = [];
d3plot = [];

for i = 1:size(dat3d,1)/2
    plot3([dat3d(i,1) dat3d(i,4)],[dat3d(i,2) dat3d(i,5)],[dat3d(i,3) dat3d(i,6)], 'LineWidth', 5);
end

title("3D Right Leaning Tree")
grid on
xlabs = [xlabs,xlabel("X")];ylabs = [ylabs,ylabel("Y")];zlabs = [zlabs,zlabel("Z")];
xlim([-120,120]);ylim([-120,120]);zlim([-120,120]);
axes = [axes,gca];

pause(3)
%plots data from 3d tree, moving
h = figure(402);
axis vis3d
filename = 'testAnimated.gif';
for p = 1:2:size(dat_3d_moving,1)
    rotate3d('on')
    

    scatter3(dat3d(1:2:end,1),dat3d(1:2:end,2),dat3d(1:2:end,3),20,...
        'MarkerEdgeColor','k',...
        'MarkerFaceColor',[1 .6 .6]);
    hold on
    scatter3(dat_3d_moving(p,1),dat_3d_moving(p,2),dat_3d_moving(p,3),20,...
        'MarkerEdgeColor','k',...
        'MarkerFaceColor',[0.6 1 .6]);
    plot3([dat_3d_moving(p,1) dat_3d_moving(p,4)],[dat_3d_moving(p,2) dat_3d_moving(p,5)],[dat_3d_moving(p,3) dat_3d_moving(p,6)], 'LineWidth', 3);
    dat_3d_moving(p,1:3)
    title("Moving Point")
    grid on
    xlabel("X");ylabel("Y");zlabel("Z");
    xlim([-120,120]);ylim([-120,120]);zlim([-120,120]);
    
    az = p;
    el = 45;
    view([az,el])
    pause(0.05)
    
    drawnow
    frame = getframe(h); 
    im = frame2im(frame); 
    [imind,cm] = rgb2ind(im,256); 
    if p == 1 
      imwrite(imind,cm,filename,'gif', 'Loopcount',inf); 
    else 
      imwrite(imind,cm,filename,'gif','WriteMode','append'); 
    end 
    hold off
end

pause(3)
%plots data from 3d tree, moving
h = figure(402);
axis vis3d
filename = 'testAnimated.gif';
for p = 1:2:size(dat_3d_moving,1)    

    scatter(dat3d(1:2:end,1),dat3d(1:2:end,2),20,...
        'MarkerEdgeColor','k',...
        'MarkerFaceColor',[1 0.6 0.6]);
    hold on
    scatter(dat_3d_moving(p,1),dat_3d_moving(p,2),20,...
        'MarkerEdgeColor','k',...
        'MarkerFaceColor',[0.6 1 0.6]);
    plot([dat_3d_moving(p,1) dat_3d_moving(p,4)],[dat_3d_moving(p,2) dat_3d_moving(p,5)], 'LineWidth', 3);
    title("Moving Point")
    grid on
    xlabel("X");ylabel("Y");
    xlim([-120,120]);ylim([-120,120]);
    
    pause(0.05)
    
    drawnow
    frame = getframe(h); 
    im = frame2im(frame); 
    [imind,cm] = rgb2ind(im,256); 
    if p == 1 
      imwrite(imind,cm,filename,'gif', 'Loopcount',inf); 
    else 
      imwrite(imind,cm,filename,'gif','WriteMode','append'); 
    end 
    hold off
end


%}
%%Aesthetics for all plots - takes handles on figure objects, modifies them
%%accordingly to be consistent
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

for j = 1:size(figs,2)
    set(figs(j),...
        'Position',[20,20,1800*0.65,1200*0.65],...
        'color','w');
end

for j = 1:size(axes,2)
    set([axes(j)],...
        'FontSize',24, ...
        'FontName', 'Arial');
end
 
for j = 1:size(legs,2)
    set(legs(j),...
        'FontSize',24, ...
        'FontName', 'Helvetica',...
        'Location','northeast',...
        'NumColumns',1,...
        'Orientation','horizontal',...
        'FontName', 'Arial');
end

labs = [xlabs,ylabs, zlabs];
for j = size(labs,2)
    set(labs,...
        'FontName', 'Arial',...
        'FontSize',24);
end

viewAngles = [-20,10;-110,10;-190,30;-290,10;-380,10];
%daspect([1,1,.3]);
OptionZ.FrameRate=20;OptionZ.Duration=10;OptionZ.Periodic=true;
%CaptureFigVid(viewAngles,'WellMadeVid',OptionZ)