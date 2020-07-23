function testexp_1(metadata)

%set experiment parameters
num_trials = 10;
num_channels = 6;

%create data and metadata struct
exp.data = nan(num_trials,num_channels);
exp.metadata = metadata;

% run experiment
for t = 1:num_trials
    pause(2)
    exp.data(t,:) = randi(10,1,num_channels); %create fake experiment data
    
    progress = 100*t/num_trials; %calculate progress of the experiment
    progress_text = ['Trial ' num2str(t) ' of ' num2str(num_trials)];
    
    %%%here, use "progress" to update the GUI's progress bar
    %%%here, use "progress_text" to update the GUI's experiment text field
end

%save exp struct
save(exp.metadata.savedir,'exp');
