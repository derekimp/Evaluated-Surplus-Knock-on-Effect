fid = fopen('/Users/zhuxinhao/Desktop/NYU/Russell_1000_component_stocks.csv');
C = textscan(fid,'%s');
fclose(fid);

C=C{1};
C(1)=[];
disp(C)

N = length(C);
A=randperm(N);
B = sort(A);

earnings={};
for i = B
    disp(C{i})
    earning = scrapeEarningsZacks(C{i})
    [m,n] = find(earning=="Mar 2020")
    if(isempty(m))
       [m,n] = find(earning=="Apr 2020")
       if(isempty(m))
            continue
       end
    end
    earning=earning(m(1),:)
    earning(7)={char(C{i})}
    earnings=[earnings;strrep(earning,',','')]
end
cell2csv("/Users/zhuxinhao/Desktop/NYU/eps.csv",strrep(earnings,',',''));

%earnings = scrapeEarningsZacks("A");
%disp("A");
%disp(earnings);
