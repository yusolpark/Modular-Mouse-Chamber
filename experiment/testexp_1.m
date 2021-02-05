
%set experiment parameters
num_trials = 10;
num_channels = 6;

%create data and metadata struct
exp.data = nan(num_trials,num_channels);
exp.metadata = app.metadata;
           
% run experiment
for t = 1:num_trials
    pause(2)
    exp.data(t,:) = randi(10,1,num_channels); %create fake experiment data
    
    progress = 100*t/num_trials; %calculate progress of the experiment
    progress_text = ['Trial ' num2str(t) ' of ' num2str(num_trials)];
    
    %%%here, use "progress" to update the GUI's progress bar
    app.ph.XData = [0 progress progress 0]; 

    %%%here, use "progress_text" to update the GUI's experiment text field
    app.ProgressTextLabel.Text = progress_text;
     
    drawnow %update graphics
end

%save exp struct
save(exp.metadata.savedir,'exp');

